#include <linux/syscalls.h>
#include <linux/sched/user.h>
#include <linux/uidgid.h>
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
    kuid_t c_uid;
    struct user_struct *user;

    if (uid == -1){
        user = get_current_user();
    }   
    else{
        c_uid.val = uid;
        user = find_user(c_uid);
    }
    if (user == NULL){
        return EINVAL;
    }
    printk("uid: %d\n", (user->uid).val);
    return (user->weight).counter;
}

SYSCALL_DEFINE2(setuserweight, int, uid, int, weight)
{  
    kuid_t c_uid;
    struct user_struct *user, *caller;

    if (weight <= 0) {
        return EINVAL;
    }

    caller = get_current_user();

    if ((caller->uid).val != 0) {
        return EACCES;
    }
    if (uid == -1){
        user = caller;
    }   
    else{
        c_uid.val = uid;
        user = find_user(c_uid);
    }
    if (user == NULL){
        return EINVAL;
    }
    printk("uid: %d\n", (user->uid).val);
    atomic_set(&user->weight, weight);
    return 0;
}