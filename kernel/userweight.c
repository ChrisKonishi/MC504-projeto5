#include <linux/syscalls.h>

#define MAX_USER 1000

void init_user_weight(int v[][2]){
    int u;
    for (u=0; u<MAX_USER; u++){
        v[u][0] = -1;
        v[u][1] = 10;
    }
}
int user_list_weight[MAX_USER][2];
int user_weight_initialized = 0;

/*  
    Como saber se o uid existe?
    Validar melhor os args
*/

SYSCALL_DEFINE1(getuserweight, int, uid)
{
    int i;
    if (!user_weight_initialized){
        init_user_weight(user_list_weight);
        user_weight_initialized = 1;
    }
    for (i=0; i<1000; i++){
        if (user_list_weight[i][0] == uid){
            return user_list_weight[i][1];
        }
    }
    return -1;
}

SYSCALL_DEFINE2(setuserweight, int, uid, int, weight)
{  
    int i;
    if (!user_weight_initialized){
        init_user_weight(user_list_weight);
        user_weight_initialized = 1;
    }
    for (i=0; i<1000; i++){
        if (user_list_weight[i][0] == -1){
            user_list_weight[i][1] = weight;
            user_list_weight[i][0] = uid;
            return 1;
        }
    }
    return -1;
}