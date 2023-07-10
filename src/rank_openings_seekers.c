#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dict.c"
#include "user_data.c"
#include "string_utils.c"

# define MAX_OPENINGS 100
# define MAX_SEEKERS 100

typedef struct {
    float scores[MAX_OPENINGS];
    Opening *openings[MAX_OPENINGS];
    int len;
} RankedOpenings;

# define MAX_SEEKERS 100

typedef struct {
    float scores[MAX_SEEKERS];
    Seeker *seekers[MAX_SEEKERS];
    int len;
} RankedSeekers;

// Returns true if both the seeker and the opening satisfy their mutual compulsory constraints, false otherwise.
bool check_compulsory_constraints(Seeker *seeker, Opening *opening) {
    EmpCons *opn_cons = &opening->compulsory_cons;
    AppCons *skr_cons = &seeker->compulsory_cons;
    TitlesCons *titles = &skr_cons->titles;
    if(titles->score != 0 && !contains(titles->titles.titles[0], LEN(titles->titles.titles[0]), titles->titles.len, opening->title)) {
        return false;
    }

    MinSalaryCons *min_sal = &skr_cons->min_sal;

    if(min_sal->score != 0 && min_sal->min_sal > opening->salary) {
        return false;
    }

    ShiftCons *shift = &skr_cons->shift;

    if(shift->score != 0 && shift->shift != 'B' && shift->shift != opening->shift) { // if 'B', means seeker will be fine with anything, if not then make sure shifts match
        return false;
    }

    LocCons *loc = &skr_cons->prefferred_location;

    if(loc->score != 0 && !contains(loc->locs.loc, LEN(loc->locs.loc[0]), loc->locs.len, opening->location)) {
        return false;
    }

    MaxHours *hours = &skr_cons->max_hours;

    if(hours->score != 0 && hours->work_hours < opening->hours) {
        return false;
    }

    MaxAgeCon *age = &opn_cons->max_age;
    if(age->score != 0 && age->max_age < seeker->age) {
        return false;
    }

    MinEduCon *edu = &opn_cons->min_edu;
    MinEduLvl *min_lvls[4] = {&edu->bachelors, &edu->masters, &edu->phd, &edu->post_doc};
    LevelsEdu *lvls = &seeker->levelsEdu;
    Majors *majors[4] = {&lvls->bachelors, &lvls->masters, &lvls->phd, &lvls->post_doc};

    for(int i = 0; i < 4; i++) {
        if(min_lvls[i]->score == 0) continue;
        bool has_lvl = false;

        for(int j = 0; j < min_lvls[i]->majors.len; j++) {
            char *cur_major = min_lvls[i]->majors.majors[j];

            for(int k = i; k < 4; k++) {
                if(contains(majors[k]->majors[0], LEN(majors[k]->majors[0]), majors[k]->len, cur_major)) {
                    has_lvl = true;    
                }
            }

        }

        if(!has_lvl) {
            return false;
        }
    }

    EqCerts *lists = &opn_cons->cert_lists.cert_lists;
    Certs *certs = &seeker->certs;
    for(int i = 0; i < NUM_CERT_LISTS; i++) {
        if(lists[i].score == 0) continue;
        Certs* list = &lists[i].certs;
        bool has_one = false;
        for(int j = 0; j < list->len; j++) {
            if(contains(certs->certs[i], LEN(certs->certs[i]), certs->len, list->certs[j])) {
                has_one = true;
            }
        }
        if(!has_one) {
            return false;
        }
    }

    ExpCon *exp_con = &opn_cons->years_exp;
    if(exp_con->score != 0) {
        DictStrInt *exp_con_dict = &exp_con->field_years_exp;
        DictStrInt *exp = &seeker->years_exp;
        for(int i = 0; i < exp_con_dict->len; i++) {
            int con_years = exp_con_dict->values[i];
            int years = 0;
            if(!dict_str_int_get(exp, exp_con_dict->keys[i], &years) || years < con_years) {
                return false;
            }
        }   
    }

    return true;
}

void filter_openings(Seeker *seeker, Opening openings[], int num_openings, RankedOpenings *ranks) {
    for(int i = 0; i < num_openings; i++) {
        if(check_compulsory_constraints(seeker, &openings[i])) {
            ranks->openings[ranks->len] = &openings[i];
            ranks->len += 1;
        }
    }
}

void filter_seekers(Opening *opening, Seeker seekers[], int num_seekers, RankedSeekers *ranks) {
    for(int i = 0; i < num_seekers; i++) {
        if(check_compulsory_constraints(opening, &seekers[i])) {
            ranks->seekers[ranks->len] = &seekers[i];
            ranks->len += 1;
        }
    }
}

float calc_score_quant(int con, int val, int base) {
    if(base == 0) return 0;
    float score = 0;
    if( val > con) {
        score = (float)base*(val/con); 
    } 
    if( val > 2*con) {
        score = 2*base;
    }

    return score;
}

void score_opening(Opening *opening, AppCons *cons) {
    int score = 0;
    AppCons *skr_cons = cons;
    TitlesCons *titles = &skr_cons->titles;
    if(titles->score != 0 && contains(titles->titles.titles[0], LEN(titles->titles.titles[0]), titles->titles.len, opening->title)) {
        score += titles->score;
    }

    MinSalaryCons *min_sal = &skr_cons->min_sal;

    score += calc_score_quant(min_sal->min_sal, opening->salary, min_sal->score);

    ShiftCons *shift = &skr_cons->shift;

    if(shift->score != 0 && (shift->shift != 'B' || shift->shift == opening->shift)) { // if 'B', means seeker will be fine with anything, if not then make sure shifts match
        score += shift->score;
    }

    LocCons *loc = &skr_cons->prefferred_location;

    if(loc->score != 0 && !contains(loc->locs.loc, LEN(loc->locs.loc[0]), loc->locs.len, opening->location)) {
        return false;
    }

    MaxHours *hours = &skr_cons->max_hours;

    if(hours->score != 0 && hours->work_hours < opening->hours) {
        return false;
    }
}

void find_and_rank_openings(Seeker *seeker, Opening openings[], int num_openings, RankedOpenings *ranks) {

}

void rank_job_openings(Seeker *seeker,Opening openings[], int num_openings) {
    RankedOpenings ranks = {0};
    filter_openings(seeker, openings, num_openings, &ranks); 
    find_and_rank_openings(seeker, openings, num_openings, &ranks);
    display_openings(&ranks);
}

void rank_seekers(Opening *opening, Seeker seekers[], int num_seekers) {
    RankedSeekers ranks = {0};
    filter_seekers(opening, seekers, num_seekers, &ranks); 
    find_and_rank_seekers(opening, seekers, num_seekers, &ranks);
    display_seekers(&ranks);
}

