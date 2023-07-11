#pragma once
#include <stdlib.h>
#include "user_data.c"
#include "form_types.c"
#include "handle_forms.c"
#include "parse_form.c"

void form_to_opening(DictStrQ *form, Opening *opening) {
    Question *q;
    dict_str_q_get(form, "0.", &q);
    strcpy(opening->path, q->response.keys[0]);
    dict_str_q_get(form, "1.", &q);
    char *name = q->response.keys[0];
    strcpy(opening->employer_name, name);
    dict_str_q_get(form, "2.", &q);
    char *title = q->response.keys[0];
    strcpy(opening->title,title);
    dict_str_q_get(form, "3.", &q);
    opening->salary = atoi(q->response.keys[0]);
    dict_str_q_get(form, "4.", &q);
    char *loc=q->response.keys[0];
    strcpy(opening->location,loc);
    dict_str_q_get(form, "5.", &q);
    char shift=q->response.keys[0][0];
    opening->shift = shift;
    dict_str_q_get(form, "6.", &q);
    // opening->hours=atoi(q->response.keys[0]);
    dict_str_q_get(form, "7.", &q);
    char *extra=q->response.keys[0];
    strcpy(opening->extra_info,extra);
    dict_str_q_get(form,"8.1.",&q);
    int score = atoi(q->response.values[0]);
    opening->desireable_cons.max_age.score = score;
    if(score != 0) {
        opening->desireable_cons.max_age.max_age=atoi(q->response.keys[1]);
    }
    dict_str_q_get(form, "8.2.1.", &q);
    score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.bachelors.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.bachelors.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.bachelors.majors.len = q->response.len-1;
    }
    
    dict_str_q_get(form, "8.2.2.", &q);
    score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.masters.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.masters.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.masters.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "8.2.3.", &q);
    score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.phd.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.phd.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.phd.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "8.2.4.", &q);
    score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.post_doc.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.post_doc.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.post_doc.majors.len = q->response.len-1;
    }


    
    for(int h = 1; h <= 3; h++) {
        char q_num[MAX_QNO_CHARS];
        snprintf(q_num, MAX_QNO_CHARS, "8.3.%d.", h);
        dict_str_q_get(form, q_num, &q);
        score = atoi(q->response.values[0]);
        opening->desireable_cons.cert_lists.cert_lists[h-1].score = score;
        if (score != 0) {
            for (int i = 1; i < q->response.len; i++) {
                strcpy(opening->desireable_cons.cert_lists.cert_lists[h-1].certs.certs[i - 1], q->response.keys[i]);
            }
            opening->desireable_cons.cert_lists.cert_lists[h-1].certs.len = q->response.len - 1;
        }
    }


    dict_str_q_get(form,"8.4.",&q);
    score = atoi(q->response.values[0]);
    opening->desireable_cons.years_exp.score = score;
    if (score != 0) {
        dict_str_int_init(&opening->desireable_cons.years_exp.field_years_exp);
        for(int i = 1; i < q->response.len; i++) {
            dict_str_int_add(&opening->desireable_cons.years_exp.field_years_exp, q->response.keys[i], atoi(q->response.values[i]));
        }
    }

    dict_str_q_get(form,"9.1.",&q);
    score = atoi(q->response.values[0]);
    opening->compulsory_cons.max_age.score = score;
    if(score != 0) {
        opening->compulsory_cons.max_age.max_age=atoi(q->response.keys[1]);
    }
    dict_str_q_get(form, "9.2.1.", &q);
    score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.bachelors.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.bachelors.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.bachelors.majors.len = q->response.len-1;
    }
    
    dict_str_q_get(form, "9.2.2.", &q);
    score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.masters.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.masters.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.masters.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "9.2.3.", &q);
    score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.phd.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.phd.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.phd.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "9.2.4.", &q);
    score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.post_doc.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.post_doc.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.post_doc.majors.len = q->response.len-1;
    }


    
    for(int j = 1; j <= 3; j++) {
        char q_num[MAX_QNO_CHARS];
        snprintf(q_num, MAX_QNO_CHARS, "9.3.%d.", j);
        dict_str_q_get(form, q_num, &q);
        score = atoi(q->response.values[0]);
        opening->compulsory_cons.cert_lists.cert_lists[j-1].score = score;
        if (score != 0) {
            for (int i = 1; i < q->response.len; i++) {
                strcpy(opening->compulsory_cons.cert_lists.cert_lists[j-1].certs.certs[i - 1], q->response.keys[i]);
            }
            opening->compulsory_cons.cert_lists.cert_lists[j-1].certs.len = q->response.len - 1;
        }
    }


    dict_str_q_get(form,"9.4.",&q);
    score = atoi(q->response.values[0]);
    opening->compulsory_cons.years_exp.score = score;
    if (score != 0) {
        dict_str_int_init(&opening->compulsory_cons.years_exp.field_years_exp);
        for(int i = 1; i < q->response.len; i++) {
            dict_str_int_add(&opening->compulsory_cons.years_exp.field_years_exp, q->response.keys[i], atoi(q->response.values[i]));
        }
    }
}


#include <stdlib.h>
#include "user_data.c"
#include "form_types.c"

void form_to_seeker(DictStrQ *form, Seeker *seeker) {
    Question *q;
    dict_str_q_get(form, "0.", &q);
    strcpy(seeker->path, q->response.keys[0]);
    dict_str_q_get(form, "1.", &q);
    DictStrStr *r = &q->response;
    char *name = r->keys[0];
    strcpy(seeker->name, name);
    dict_str_q_get(form, "2.", &q);
    r = &q->response;
    char *age = r->keys[0];
    seeker->age = atoi(age);
    dict_str_q_get(form, "3.", &q);
    char gender=q->response.keys[0][0];
    seeker->gender = gender;
    dict_str_q_get(form, "4.", &q);
    char *email=q->response.keys[0];
    strcpy(seeker->email,email);
    dict_str_q_get(form, "5.", &q);
    char *phone_no=q->response.keys[0];
    strcpy(seeker->phone_no,phone_no);
    dict_str_q_get(form, "6.", &q);
    //Address for seeker
    dict_str_q_get(form, "7.1.", &q);

    for(int i = 0; i < q->response.len; i++) {
        strcpy(seeker->levelsEdu.bachelors.majors[i],q->response.keys[i]);
    }
    seeker->levelsEdu.bachelors.len = q->response.len;
    dict_str_q_get(form,"7.2.",&q);
    seeker->levelsEdu.masters.len = q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->levelsEdu.masters.majors[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"7.3.",&q);
    seeker->levelsEdu.phd.len = q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->levelsEdu.phd.majors[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"7.4.",&q);
    seeker->levelsEdu.post_doc.len = q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->levelsEdu.post_doc.majors[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"8.",&q);
    seeker->certs.len=q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->certs.certs[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"9.",&q);
    dict_str_int_init(&seeker->years_exp);
    for(int i=0;i<q->response.len;i++){
        dict_str_int_add(&seeker->years_exp, q->response.keys[i], atoi(q->response.values[i]));
    }
    dict_str_q_get(form,"10.1.1.",&q);
    strcpy(seeker->proj_details[0].title,q->response.keys[0]);
    dict_str_q_get(form,"10.1.2.",&q);
    strcpy(seeker->proj_details[0].employer_name,q->response.keys[0]);
    dict_str_q_get(form,"10.1.3.",&q);
    strcpy(seeker->proj_details[0].address,q->response.keys[0]);
    dict_str_q_get(form,"10.1.4.",&q);
    seeker->proj_details[0].salary = atoi(q->response.keys[0]);
    dict_str_q_get(form,"10.1.5.",&q);
    strcpy(seeker->proj_details[0].start_date,q->response.keys[0]);
    dict_str_q_get(form,"10.1.6.",&q);
    strcpy(seeker->proj_details[0].end_date,q->response.keys[0]);
    dict_str_q_get(form,"10.1.7.",&q);
    strcpy(seeker->proj_details[0].other_details,q->response.keys[0]);
    dict_str_q_get(form,"10.2.1.",&q);
    strcpy(seeker->proj_details[1].title,q->response.keys[0]);
    dict_str_q_get(form,"10.2.2.",&q);
    strcpy(seeker->proj_details[1].employer_name,q->response.keys[0]);
    dict_str_q_get(form,"10.2.3.",&q);
    strcpy(seeker->proj_details[1].address,q->response.keys[0]);
    dict_str_q_get(form,"10.2.4.",&q);
    seeker->proj_details[1].salary = atoi(q->response.keys[0]);
    dict_str_q_get(form,"10.2.5.",&q);
    strcpy(seeker->proj_details[1].start_date,q->response.keys[0]);
    dict_str_q_get(form,"10.2.6.",&q);
    strcpy(seeker->proj_details[1].end_date,q->response.keys[0]);
    dict_str_q_get(form,"10.2.7.",&q);
    strcpy(seeker->proj_details[1].other_details,q->response.keys[0]);
    dict_str_q_get(form,"10.3.1.",&q);
    strcpy(seeker->proj_details[2].title,q->response.keys[0]);
    dict_str_q_get(form,"10.3.2.",&q);
    strcpy(seeker->proj_details[2].employer_name,q->response.keys[0]);
    dict_str_q_get(form,"10.3.3.",&q);
    strcpy(seeker->proj_details[2].address,q->response.keys[0]);
    dict_str_q_get(form,"10.3.4.",&q);
    seeker->proj_details[2].salary = atoi(q->response.keys[0]);
    dict_str_q_get(form,"10.3.5.",&q);
    strcpy(seeker->proj_details[2].start_date,q->response.keys[0]);
    dict_str_q_get(form,"10.3.6.",&q);
    strcpy(seeker->proj_details[2].end_date,q->response.keys[0]);
    dict_str_q_get(form,"10.3.7.",&q);
    strcpy(seeker->proj_details[2].other_details,q->response.keys[0]);
    dict_str_q_get(form,"11.",&q);
    strcpy(seeker->extra_info,q->response.keys[0]);
    dict_str_q_get(form,"12.1.",&q);
    int score = atoi(q->response.values[0]);
    seeker->desireable_cons.titles.score=score;
    if (score!=0){   
        for(int i = 1; i < q->response.len; i++) {
            strcpy(seeker->desireable_cons.titles.titles.titles[i-1],q->response.keys[i]);
        }
        seeker->desireable_cons.titles.titles.len = q->response.len-1;
    }

    dict_str_q_get(form,"12.2.",&q);

    score = atoi(q->response.values[0]);
    seeker->desireable_cons.min_sal.score=score;
    if (score!=0){
        seeker->desireable_cons.min_sal.min_sal=atoi(q->response.keys[1]);
    }
    dict_str_q_get(form,"12.3.",&q);
    score = atoi(q->response.values[0]);
    seeker->desireable_cons.shift.score=score;
    if (score!=0){
            seeker->desireable_cons.shift.shift=q->response.keys[1][0];
    }
    dict_str_q_get(form,"12.4.",&q);
    score = atoi(q->response.values[0]);
    seeker->desireable_cons.prefferred_location.score=score;
    if (score!=0){
        for(int i=1;i<q->response.len;i++){
            strcpy(seeker->desireable_cons.prefferred_location.locs.loc[i-1],q->response.keys[i]);
        }
        seeker->desireable_cons.prefferred_location.locs.len = q->response.len-1;
    }
    
    dict_str_q_get(form,"12.5.",&q);
    score = atoi(q->response.values[0]);
    seeker->desireable_cons.max_hours.score=score;
    if (score!=0){
        seeker->desireable_cons.max_hours.work_hours=atoi(q->response.keys[1]);
    }

    // dict_str_q_get(form,"12.1.",&q);
    // score = atoi(q->response.values[0]);
    // seeker->desireable_cons.titles.score=score;
    // if (score!=0){   
    //     for(int i = 1; i < q->response.len; i++) {
    //         strcpy(seeker->desireable_cons.titles.titles.titles[i-1],q->response.keys[i]);
    //     }
    //     seeker->desireable_cons.titles.titles.len = q->response.len-1;
    // }

    // dict_str_q_get(form,"12.2.",&q);

    // score = atoi(q->response.values[0]);
    // seeker->desireable_cons.min_sal.score=score;
    // if (score!=0){
    //     seeker->desireable_cons.min_sal.min_sal=atoi(q->response.keys[1]);
    // }
    // dict_str_q_get(form,"12.3.",&q);
    // score = atoi(q->response.values[0]);
    // seeker->desireable_cons.shift.score=score;
    // if (score!=0){
    //         seeker->desireable_cons.shift.shift=q->response.keys[1][0];
    // }
    // dict_str_q_get(form,"12.4.",&q);
    // score = atoi(q->response.values[0]);
    // seeker->desireable_cons.prefferred_location.score=score;
    // if (score!=0){
    //     for(int i=1;i<q->response.len;i++){
    //         strcpy(seeker->desireable_cons.prefferred_location.locs.loc[i-1],q->response.keys[i]);
    //     }
    //     seeker->desireable_cons.prefferred_location.locs.len = q->response.len-1;
    // }
    
    // dict_str_q_get(form,"12.5.",&q);
    // score = atoi(q->response.values[0]);
    // seeker->desireable_cons.max_hours.score=score;
    // if (score!=0){
    //     seeker->desireable_cons.max_hours.work_hours=atoi(q->response.keys[1]);
    // }

    dict_str_q_get(form,"13.1.",&q);
    score = atoi(q->response.values[0]);
    seeker->compulsory_cons.titles.score=score;
    if (score!=0){   
        for(int i = 1; i < q->response.len; i++) {
            strcpy(seeker->compulsory_cons.titles.titles.titles[i-1],q->response.keys[i]);
        }
        seeker->compulsory_cons.titles.titles.len = q->response.len-1;
    }

    dict_str_q_get(form,"13.2.",&q);

    score = atoi(q->response.values[0]);
    seeker->compulsory_cons.min_sal.score=score;
    if (score!=0){
        seeker->compulsory_cons.min_sal.min_sal=atoi(q->response.keys[1]);
    }
    dict_str_q_get(form,"13.3.",&q);
    score = atoi(q->response.values[0]);
    seeker->compulsory_cons.shift.score=score;
    if (score!=0){
            seeker->compulsory_cons.shift.shift=q->response.keys[1][0];
    }
    dict_str_q_get(form,"13.4.",&q);
    score = atoi(q->response.values[0]);
    seeker->compulsory_cons.prefferred_location.score=score;
    if (score!=0){
        for(int i=1;i<q->response.len;i++){
            strcpy(seeker->compulsory_cons.prefferred_location.locs.loc[i-1],q->response.keys[i]);
        }
        seeker->compulsory_cons.prefferred_location.locs.len = q->response.len-1;
    }
    
    dict_str_q_get(form,"13.5.",&q);
    score = atoi(q->response.values[0]);
    seeker->compulsory_cons.max_hours.score=score;
    if (score!=0){
        seeker->compulsory_cons.max_hours.work_hours=atoi(q->response.keys[1]);
    }
}

void form_to_seeker_test() {
    char path[100];
	get_good_form_path("example/Applicants/index.txt", path);
	printf("%s\n", path);
    DictStrQ form = {0};
    dict_str_q_init(&form);
    get_form(path, &form);
    dict_str_q_print(&form);
    Seeker seeker = {0};
    form_to_seeker(&form, &seeker);
}

void form_to_opening_test() {
    char path[100];
	get_good_form_path("example/Job Openings/index.txt", path);
	printf("%s\n", path);
    DictStrQ form = {0};
    dict_str_q_init(&form);
    get_form(path, &form);
    dict_str_q_print(&form);
    Opening opening = {0};
    form_to_opening(&form, &opening);
}



void main() {
    form_to_opening_test();
}