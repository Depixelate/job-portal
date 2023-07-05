#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dict.c"
#include "user_data.c"

# define MAX_OPENINGS 100

typedef struct {
    float scores[MAX_OPENINGS];
    Opening *openings[MAX_OPENINGS];
    int len;
} RankedOpenings;

// Returns true if both the seeker and the opening satisfy their mutual compulsory constraints, false otherwise.
bool check_compulsory_constraints(Seeker *seeker, Opening *opening) {
    EmpCons *opn_cons = opening->compulsory_cons;
    AppCons *skr_cons = seeker->compulsory_cons;
    TitlesCons *titles = &skr_cons->titles;
    if(titles->score != 0 && !contains(titles->titles.titles, titles->titles.len, opening->title) {
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

    if(loc->score != 0 && !contains(loc->locs->loc, loc->locs->len, opening->location)) {
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

        for(int j = 0; j < min_lvls[i]->majors.len; j++) {
            bool has_lvl = false;
            char *cur_major = min_lvls[i]->majors.majors[j];

            for(int k = i; k < 4; k++) {
                if(contains(majors[k]->majors, majors[k]->len, cur_major)) {
                    has_lvl = true;    
                }
            }

            if(!has_lvl) {
                return false;
            }
        }
    }

    EqCerts *lists = &opn_cons->cert_lists.cert_lists;
    Certs *certs = &seeker->certs;
    for(int i = 0; i < NUM_CERT_LISTS; i++) {
        if(lists[i]->score == 0) continue;
        list = lists[i].certs;
    }

}

void filter_openings(Seeker *seeker, Opening openings[], int num_openings) {
    
}

void rank_job_openings(Seeker *seeker,Opening openings[], int num_openings) {
    filter_openings(seeker, openings, num_openings); 
    RankedOpenings ranks;
    find_and_rank_openings(seeker, openings, num_openings, &ranks);
    display_openings(&ranks);
}

