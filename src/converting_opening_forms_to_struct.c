#include <stdlib.h>
#include "user_data.c"
#include "form_types.c"

void form_to_opening(DictStrQ *form, Opening *opener) {
    Question *q;
    dict_str_q_get(form, "1.", &q);
    Response *r = q->response;
    char *name = response.keys[0];
    strcpy(opener->name, name);
    dict_str_q_get(form, "2.", &q);
    r = q->response;
    char *title = response.keys[0];
    strcpy(opener->title,title);
    dict_str_q_get(form, "3.", &q);
    opener->salary = atoi(q->response.keys[0]);
    dict_str_q_get(form, "4.", &q);
    char *loc=q->response.keys[0];
    strcpy(opener->location,loc);
    dict_str_q_get(form, "5.", &q);
    char *shift=q->response.keys[0][0];
    strcpy(opener->shift,shift);
    dict_str_q_get(form, "6.", &q);
    opener->hours=atoi(q->response.keys[0]);
    dict_str_q_get(form, "7.", &q);
    char *extra=q->response.keys[0];
    strcpy(opener->extra_info,extra);
    dict_str_q_get(form,"8.1.",&q);
    opener->desirable_cons.max_age.max_age=atoi(q->response.keys[0]);
    opener->desirable_cons.max_age.score=atoi(q->response.values[0]);
    dict_str_q_get(form,"8.2.1.",&q);
    for(int i = 0; i < q->response.len; i++) {
        strcpy(opener->desirable_cons.min_edu.bach.majors[i],q->response.keys[i]);
    }
    opener->desirable_cons.min_edu.bach.score = q->response.values[0];
    dict_str_q_get(form,"8.2.2.",&q);
    for(int i-0;i<q->response.len;i++){}
    strcpy(opener->desirable_cons.min_edu.mast.majors[i] ,q->response.keys[i];
    }
    opener->desirable_cons.min_edu.mast.score=atoi(q->response.values[0]);
    dict_str_q_get(form,"8.2.3.",&q);
    for(int i=0;i<q->response.len;i++){
        strcpy( opener->desirable_cons.min_edu.phd.majors[i],q->response.keys[i]);
    }
    opener->desirable_cons.min_edu.phd.score=atoi(q->response.values[0]);
    dict_str_q_get(form."8.2.4",&q);
    for(int i=0;i<q->response.len;i++){
        strcpy(opener->desirable_cons.min_edu.post.majors[i],q->response.keys[i]);
    }
    opener->desirable_cons.min_edu.post.score=atoi(q->response.values[0]);    
    
    dict_str_q_get(form,"8.3.1.",&q);
    opener->desirable_cons.cert_lists.cert_lists.score=atoi(q->response.values[0]);
    for(int i=0;i,q->resonse.len;i++){
        strcpy(opener->desirable_cons.cert_lists.cert_lists[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"8.3.2.",&q);
    opener->desirable_cons.cert_lists.cert_lists.score=atoi(q->response.values[0]);
    for(int i=0;i,q->resonse.len;i++){
        strcpy(opener->desirable_cons.cert_lists.cert_lists[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"8.3.3.",&q);
    opener->desirable_cons.cert_lists.cert_lists.score=atoi(q->response.values[0]);
    for(int i=0;i,q->resonse.len;i++){
        strcpy(opener->desirable_cons.cert_lists.cert_lists[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"8.4.",&q);
    opener->desirable_cons.years_exp.score=q->response.values[0];

    for(int i=1;i<q->response.len;i++){
        strcpy(opener->desirable_cons.years_exp.keys[i],q->respose.keys[i]);
        opener->desirable_cons.years_exp.values[i]=atoi(q->response.values[i]);
    }
    dict_str_q_get(form,"9.1.",&q);
    opener->compulsory_cons.max_age.max_age=atoi(q->response.keys[0]);
    opener->compulsory_cons.max_age.score=atoi(q->response.values[0]);
    dict_str_q_get(form,"9.2.1.",&q);
    for(int i = 0; i < q->response.len; i++) {
        strcpy(opener->compulsory_cons.min_edu.bach.majors[i],q->response.keys[i]);
    }
    opener->compulsory_cons.min_edu.bach.score = q->response.values[0];
    dict_str_q_get(form,"9.2.2.",&q);
    for(int i-0;i<q->response.len;i++){}
    strcpy(opener->compulsory_cons.min_edu.mast.majors[i] ,q->response.keys[i];
    }
    opener->compulsory_cons.min_edu.mast.score=atoi(q->response.values[0]);
    dict_str_q_get(form,"9.2.3.",&q);
    for(int i=0;i<q->response.len;i++){
        strcpy( opener->compulsory_cons.min_edu.phd.majors[i],q->response.keys[i]);
    }
    opener->compulsory_cons.min_edu.phd.score=atoi(q->response.values[0]);
    dict_str_q_get(form."9.2.4",&q);
    for(int i=0;i<q->response.len;i++){
        strcpy(opener->compulsory_cons.min_edu.post.majors[i],q->response.keys[i]);
    }
    opener->compulsory_cons.min_edu.post.score=atoi(q->response.values[0]);    
    
    dict_str_q_get(form,"9.3.1.",&q);
    opener->compulsory_cons.cert_lists.cert_lists.score=atoi(q->response.values[0]);
    for(int i=0;i,q->resonse.len;i++){
        strcpy(opener->compulsory_cons.cert_lists.cert_lists[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"9.3.2.",&q);
    opener->compulsory_cons.cert_lists.cert_lists.score=atoi(q->response.values[0]);
    for(int i=0;i,q->resonse.len;i++){
        strcpy(opener->compulsory_cons.cert_lists.cert_lists[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"9.3.3.",&q);
    opener->desirable_cons.cert_lists.cert_lists.score=atoi(q->response.values[0]);
    for(int i=0;i,q->resonse.len;i++){
        strcpy(opener->desirable_cons.cert_lists.cert_lists[i],q->response.keys[i]);
    }
    dict_str_q_get(form,"9.4.",&q);
    opener->compulsory_cons.years_exp.score=q->response.values[0];

    for(int i=1;i<q->response.len;i++){
        strcpy(opener->compulsory_cons.years_exp.keys[i],q->respose.keys[i]);
        opener->compulsory_cons.years_exp.values[i]=atoi(q->response.values[i]);
    }
}

