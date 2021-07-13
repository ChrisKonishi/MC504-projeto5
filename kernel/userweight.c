#include <linux/syscalls.h>
#include <linux/sched/user.h>
#include <linux/uidgid.h>
#include <linux/cred.h>

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
    /* printk("uid: %d\n", (user->uid).val); */
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
    /* printk("uid: %d\n", (user->uid).val); */
    atomic_set(&user->weight, weight);
    return 0;
}