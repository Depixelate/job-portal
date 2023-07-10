#include <stdlib.h>
#include "user_data.c"
#include "form_types.c"

void form_to_opening(DictStrQ *form, Opening *opening) {
    Question *q;
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
    strcpy(opening->shift,shift);
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
    int score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.bachelors.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.bachelors.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.bachelors.majors.len = q->response.len-1;
    }
    
    dict_str_q_get(form, "8.2.2.", &q);
    int score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.masters.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.masters.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.masters.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "8.2.3.", &q);
    int score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.phd.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.phd.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.phd.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "8.2.4.", &q);
    int score = atoi(q->response.values[0]);
    opening->desireable_cons.min_edu.post_doc.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->desireable_cons.min_edu.post_doc.majors.majors[i-1],q->response.keys[i]);
        }
        opening->desireable_cons.min_edu.post_doc.majors.len = q->response.len-1;
    }


    
    for(int h = 1; h <= 3; h++) {
        char q_num[MAX_QNO_CHARS];
        snprintf(q_num, MAX_QNO_CHARS, "8.3.%d", h);
        dict_str_q_get(form, q_num, &q);
        int score = atoi(q->response.values[0]);
        opening->desireable_cons.cert_lists.cert_lists[h-1].score = score;
        if (score != 0) {
            for (int i = 1; i < q->response.len; i++) {
                strcpy(opening->desireable_cons.cert_lists.cert_lists[h-1].certs.certs[i - 1], q->response.keys[i]);
            }
            opening->desireable_cons.cert_lists.cert_lists[h-1].certs.len = q->response.len - 1;
        }
    }


    dict_str_q_get(form,"8.4.",&q);
    int score = atoi(q->response.values[0]);
    opening->desireable_cons.years_exp.score = score;
    if (score != 0) {
        dict_str_int_init(&opening->desireable_cons.years_exp.field_years_exp);
        for(int i = 1; i < q->response.len; i++) {
            dict_str_int_add(&opening->desireable_cons.years_exp.field_years_exp, q->response.keys[i], atoi(q->response.values[i]));
        }
    }

    dict_str_q_get(form,"9.1.",&q);
    int score = atoi(q->response.values[0]);
    opening->compulsory_cons.max_age.score = score;
    if(score != 0) {
        opening->compulsory_cons.max_age.max_age=atoi(q->response.keys[1]);
    }
    dict_str_q_get(form, "9.2.1.", &q);
    int score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.bachelors.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.bachelors.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.bachelors.majors.len = q->response.len-1;
    }
    
    dict_str_q_get(form, "9.2.2.", &q);
    int score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.masters.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.masters.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.masters.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "9.2.3.", &q);
    int score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.phd.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.phd.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.phd.majors.len = q->response.len-1;
    }

    dict_str_q_get(form, "9.2.4.", &q);
    int score = atoi(q->response.values[0]);
    opening->compulsory_cons.min_edu.post_doc.score = score;
    if(score != 0) {
        for(int i = 1; i < q->response.len; i++) {
            strcpy(opening->compulsory_cons.min_edu.post_doc.majors.majors[i-1],q->response.keys[i]);
        }
        opening->compulsory_cons.min_edu.post_doc.majors.len = q->response.len-1;
    }


    
    for(int j = 1; j <= 3; j++) {
        char q_num[MAX_QNO_CHARS];
        snprintf(q_num, MAX_QNO_CHARS, "9.3.%d", j);
        dict_str_q_get(form, q_num, &q);
        int score = atoi(q->response.values[0]);
        opening->compulsory_cons.cert_lists.cert_lists[j-1].score = score;
        if (score != 0) {
            for (int i = 1; i < q->response.len; i++) {
                strcpy(opening->compulsory_cons.cert_lists.cert_lists[j-1].certs.certs[i - 1], q->response.keys[i]);
            }
            opening->compulsory_cons.cert_lists.cert_lists[j-1].certs.len = q->response.len - 1;
        }
    }


    dict_str_q_get(form,"9.4.",&q);
    int score = atoi(q->response.values[0]);
    opening->compulsory_cons.years_exp.score = score;
    if (score != 0) {
        dict_str_int_init(&opening->compulsory_cons.years_exp.field_years_exp);
        for(int i = 1; i < q->response.len; i++) {
            dict_str_int_add(&opening->compulsory_cons.years_exp.field_years_exp, q->response.keys[i], atoi(q->response.values[i]));
        }
    }
}

