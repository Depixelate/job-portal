#include <stdlib.h>
#include "user_data.c"
#include "form_types.c"

void form_to_seeker(DictStrQ *form, Seeker *seeker) {
    Question *q;
    dict_str_q_get(form, "1.", &q);
    Response *r = q->response;
    char *name = response.keys[0];
    strcpy(seeker->name, name);
    dict_str_q_get(form, "2.", &q);
    r = q->response;
    char *age = response.keys[0];
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
        strcpy(seeker->levelsEdu.bachelor.majors[i],q->response.keys[i]);
    }
    seeker->levelsEdu.bachelor.len = q->response.len;
    dict_str_q_get(form,"7.2.",&q);
    seeker->levelsEdu.masters.len = q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->levelsEdu.masters.majors[i],q->response.keys[i]);
    }
    dict_str_q_get(form."7.3.",&q)
    seeker->levelsEdu.phd.len = q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->levelEdu.phd.majors[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"7.4.".&q);
    seeker->levelsEdu.post_doc.len = q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->levelsEdu.post_doc.majors[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"8.",&q);
    seeker->certs.len=q->response.len;
    for(int i=0;i,q->resonse.len;i++){
        strcpy(seeker->certs.certs[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"9.",&q);
    seeker->years_exp.len=q->response.len;
    for(int i=0;i<q->response.len;i++){
        strcpy(seeker->years_exp.keys[i],q->respose.keys[i]);
        seeker->years_exp.values[i]=atoi(q->response.values[i]);
    }
    dict_str_q_get(form,"10.1.1.",&q);
    strcpy(seeker->proj_details[0].title,q->response.keys[0]);
    dict_str_q_get(form,"10.1.2.",&q);
    strcpy(seeker->proj_details[0].employer_name,q->response.keys[0]);
    dict_str_q_get(form,"10.1.3.",&q);
    strcpy(seeker->proj_details[0].address,q->response.keys[0])
    dict_str_q_get(form,"10.1.4.",&q);
    strcpy(seeker->proj_details[0].salary,q->response.keys[0]);
    dict_str_q_get(form,"10.1.5",&q);
    srtcpy(seeker->proj_details[0].start_date,q->response.keys[0]);
    dict_str_q_get(form,"10.1.6.",&q);
    strcpy(seeker->proj_details[0].end_date,q->response.keys[0]);
    dict_str_q_get(form,"10.1.7",&q);
    strcpy(seeker->proj_details[0].other_details,q->response.keys[0]);
    dict_str_q_get(form,"10.2.1.",&q);
    strcpy(seeker->proj_details[1].title,q->response.keys[0]);
    dict_str_q_get(form,"10.2.2.",&q);
    strcpy(seeker->proj_details[1].employer_name,q->response.keys[0]);
    dict_str_q_get(form,"10.2.3.",&q);
    strcpy(seeker->proj_details[1].address,q->response.keys[0])
    dict_str_q_get(form,"10.2.4.",&q);
    strcpy(seeker->proj_details[1].salary,q->response.keys[0]);
    dict_str_q_get(form,"10.2.5",&q);
    srtcpy(seeker->proj_details[1].start_date,q->response.keys[0]);
    dict_str_q_get(form,"10.2.6.",&q);
    strcpy(seeker->proj_details[1].end_date,q->response.keys[0]);
    dict_str_q_get(form,"10.2.7",&q);
    strcpy(seeker->proj_details[1].other_details,q->response.keys[0]);
    dict_str_q_get(form,"10.3.1.",&q);
    strcpy(seeker->proj_details[2].title,q->response.keys[0]);
    dict_str_q_get(form,"10.3.2.",&q);
    strcpy(seeker->proj_details[2].employer_name,q->response.keys[0]);
    dict_str_q_get(form,"10.3.3.",&q);
    strcpy(seeker->proj_details[2].address,q->response.keys[0])
    dict_str_q_get(form,"10.3.4.",&q);
    strcpy(seeker->proj_details[2].salary,q->response.keys[0]);
    dict_str_q_get(form,"10.3.5",&q);
    srtcpy(seeker->proj_details[2].start_date,q->response.keys[0]);
    dict_str_q_get(form,"10.3.6.",&q);
    strcpy(seeker->proj_details[2].end_date,q->response.keys[0]);
    dict_str_q_get(form,"10.3.7",&q);
    strcpy(seeker->proj_details[2].other_details,q->response.keys[0]);
    dict_str_q_get(form,"11.",&q);
    strcpy(seeker->extra_info,q->response.keys[0]);
    dict_str_q_get(form,"12.1.",&q);
    if (q->response.values[0]!=0){
        for(int i = 1; i < q->response.len; i++) {
        strcpy(seeker->desireable_cons.titles.titles[i],q->response.keys[i]);
        seeker->desireable_cons.titles.score[i]=atoi(q->response.values[i]);
        }
    }
    else
       seeker->desirable_cons.titles.score=0;
    dict_str_q_get(form,"12.2.",&q);
    if (q->response.values[0]!=0){
        seeker->desirable_cons.min_sal.min_sal=atoi(q->response.keys[0]);
        seeker->desirable_cons.min_sal.score=atoi(q->response.values[0]);
    }
    else
       seeker->desirable_cons.min_sal.score=0;
    dict_str_q_get(for,"12.3.",&q);
    if (q->response.values[0]!=0){
            strcpy(seeker->desirable_cons.shift.shift,q->response.keys[i][0]);
            seeker->desirable_cons.shift.score=q->response.values[i]
        
    }
    else
       seeker->desirable_cons.score=0;
    dict_str_q_get(form,"12.4.",&q);
    if (q->response.values[0]!=0){
        for(int i=0;i<q->response.len;i++){
            strcpy(seeker->desirable_cons.prefferred_location.locs.loc[i],q->response.keys[i]);
            seeker->desirable_cons.prefferred_locations.score=atoi(q->response.values[i]);
        }
    }
    else
       seeker->desirable_cons.prefferred_location.score=0;
    
    dict_str_q_get(form,"12.5.",&q);
    if (q->response.values[0]!=0){
        seeker->desirable_cons.max_hours.work_hours=atoi(q->response.keys[0]);
        seeker->desirable_cons.max_hours.score=atoi(q->response.values[0]);
    }
    else
      seeker->desirable_cons.max_hours.score=0;

    dict_str_q_get(form,"13.1.",&q);
    if (q->response.values[0]!=0){
        for(int i = 1; i < q->response.len; i++) {
        strcpy(seeker->compulsory_cons.titles.titles[i],q->response.keys[i]);
        seeker->compulsory_cons.titles.score[i]=atoi(q->response.values[i]);
        }
    }
    else
       seeker->compulsory_cons.titles.score=0;
    dict_str_q_get(form,"13.2.",&q);
    if (q->response.values[0]!=0){
        seeker->compulsory_cons.min_sal.min_sal=atoi(q->response.keys[0]);
        seeker->compulsory_cons.min_sal.score=atoi(q->response.values[0]);
    }
    else
       seeker->compulsory_cons.min_sal.score=0;
    dict_str_q_get(for,"13.3.",&q);
    if (q->response.values[0]!=0){
            strcpy(seeker->compulsory_cons.shift.shift,q->response.keys[i][0]);
            seeker->compulsory_cons.shift.score=q->response.values[i]
        
    }
    else
       seeker->compulsory_cons.score=0;
    dict_str_q_get(form,"13.4.",&q);
    if (q->response.values[0]!=0){
        for(int i=0;i<q->response.len;i++){
            strcpy(seeker->compulsory_cons.prefferred_location.locs.loc[i],q->response.keys[i]);
            seeker->compulsory_cons.prefferred_locations.score=atoi(q->response.values[i]);
        }
    }
    else
       seeker->compulsory_cons.prefferred_location.score=0;
    
    dict_str_q_get(form,"13.5.",&q);
    if (q->response.values[0]!=0){
        seeker->compulsory_cons.max_hours.work_hours=atoi(q->response.keys[0]);
        seeker->compulsory_cons.max_hours.score=atoi(q->response.values[0]);
    }
    else
      seeker->compulsory_cons.max_hours.score=0;
}