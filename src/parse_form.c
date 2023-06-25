// Check for newline, then check for %d.%d.%d., then read everything upto colon, then read rest of text as key-value pairs until newline %d.%d.%d.%d.
#define MAX_QNO_CHARS 10
#define MAX_QUESTION_CHARS 200
#define MAX_ANS_KV_PAIRS 10
 
typedef struct {
    char number[MAX_QNO_CHARS];
    char question[MAX_QUESTION_CHARS];
    char 
} Question;

typedef struct {
    Question questions[100];
    int len;
} Form;
