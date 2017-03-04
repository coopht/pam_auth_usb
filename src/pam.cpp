#define PAM_SM_AUTH

#include <security/pam_modules.h>
#include <syslog.h>
#include <security/pam_ext.h>

#include "usb_device.h"

#define UNUSED __attribute__ ((unused))

extern "C"
{

/* expected hook */
PAM_EXTERN
int
pam_sm_setcred(pam_handle_t *ph,
               int flags UNUSED,
               int argc UNUSED,
               const char **argv UNUSED)
{
    pam_syslog(ph, LOG_WARNING, "%s : %s", __PRETTY_FUNCTION__, "PAM_SUCCESS");
    // TODO implement this function
    return PAM_SUCCESS;
}

PAM_EXTERN
int pam_sm_acct_mgmt(pam_handle_t *ph,
                     int flags UNUSED,
                     int argc UNUSED,
                     const char **argv UNUSED)
{
    pam_syslog(ph, LOG_WARNING, "%s : %s", __PRETTY_FUNCTION__, "PAM_SUCCESS");
    // TODO implement this function
    return PAM_SUCCESS;
}

PAM_EXTERN
int
pam_sm_authenticate(pam_handle_t *ph UNUSED,
                    int flags UNUSED,
                    int argc UNUSED,
                    const char **argv UNUSED)
{
    if (isDeviceConnected()) {
        return PAM_SUCCESS;
    }

    return PAM_AUTH_ERR;
}

}
