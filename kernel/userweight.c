#include <linux/syscalls.h>
#include <linux/sched/user.h>
#include <linux/uidgid.h>
//#include <sys/types.h>
#include <linux/cred.h>

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
        Em user.h/user.c, tem um find_user, talvez dê para usar, modificar a struct de user para algo bem mais elegante
    Validar melhor os args
    Como saber o uid do user atual? Se o uid for -1, indica user atual
*/

SYSCALL_DEFINE1(getuserweight, int, uid)
{
    int i;
    int c_uid;
    if (!user_weight_initialized){
        init_user_weight(user_list_weight);
        user_weight_initialized = 1;
    }
    if (uid == -1){
        c_uid = (int) (get_current_user()->uid).val;
    }   
    else{
        c_uid = uid;
    }

    for (i=0; i<1000; i++){
        if (user_list_weight[i][0] == c_uid){
            return user_list_weight[i][1];
        }
    }
    return -1;
}

SYSCALL_DEFINE2(setuserweight, int, uid, int, weight)
{  
    int i, c_uid;
    if (!user_weight_initialized){
        init_user_weight(user_list_weight);
        user_weight_initialized = 1;
    }

    if (uid == -1){
        c_uid = (int) (get_current_user()->uid).val;
    }   
    else{
        c_uid = uid;
    }

    for (i=0; i<1000; i++){
        if (user_list_weight[i][0] == -1){
            user_list_weight[i][1] = weight;
            user_list_weight[i][0] = c_uid;
            return 1;
        }
    }
    return -1;
}