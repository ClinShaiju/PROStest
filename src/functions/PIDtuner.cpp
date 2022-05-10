#include "main.h"

static lv_obj_t* kp;
static lv_obj_t* ki;
static lv_obj_t* kd;

static void getPIDvalues(void) {
    static char buffer[32];
    snprintf(buffer, 32, "kP: %d", kP);
    lv_label_set_text(kp, buffer);

    static char otherBuffer[32];
    snprintf(otherBuffer, 32, "kI: %d", kI);
    lv_label_set_text(kp, otherBuffer);

    static char notOtherBuffer[32];
    snprintf(notOtherBuffer, 32, "kP: %d", kD);
    lv_label_set_text(kp, notOtherBuffer);
}

static lv_res_t kpUp_action(lv_obj_t * btn) {
    kP+=.05;
    getPIDvalues();

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kpDown_action(lv_obj_t * btn) {
    kP-=.05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kiUp_action(lv_obj_t * btn) {
    kI+=.05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kiDown_action(lv_obj_t * btn) {
    kI-=.05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kdUp_action(lv_obj_t * btn) {
    kD+=.05;   
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kdDown_action(lv_obj_t * btn) {
    kD-=.05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void PIDtuner(void) {
    //480 x 272 pixels

    //create screen to change k values
    lv_obj_t* settingsScr = lv_obj_create(NULL, NULL);

    lv_scr_load(settingsScr);

    //create settings title
    lv_obj_t * settingsTitle = lv_label_create(settingsScr, NULL);
    lv_label_set_text(settingsTitle, "Settings");
    lv_obj_align(settingsTitle, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

    //create buttons to change k values
    lv_obj_t* kpUp = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kpDown = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kiUp = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kiDown = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kdUp = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kdDown = lv_btn_create(settingsScr, NULL);

    //k button labels
    lv_obj_t* kpUpLabel = lv_label_create(kpUp, NULL);
    lv_obj_t* kpDownLabel = lv_label_create(kpDown, NULL);
    lv_obj_t* kiUpLabel = lv_label_create(kiUp, NULL);
    lv_obj_t* kiDownLabel = lv_label_create(kiDown, NULL);
    lv_obj_t* kdUpLabel = lv_label_create(kdUp, NULL);
    lv_obj_t* kdDownLabel = lv_label_create(kdDown, NULL);

    //set text for k setting labels
    lv_label_set_text(kpUpLabel, "+kP");
    lv_label_set_text(kiUpLabel, "+kI");
    lv_label_set_text(kdUpLabel, "+kD");
    lv_label_set_text(kpDownLabel, "-kP");
    lv_label_set_text(kiDownLabel, "-kI");
    lv_label_set_text(kdDownLabel, "-kD");

    //set k button actions
    lv_btn_set_action(kpUp, LV_BTN_ACTION_CLICK, kpUp_action);
    lv_btn_set_action(kpDown, LV_BTN_ACTION_CLICK, kpDown_action);
    lv_btn_set_action(kiUp, LV_BTN_ACTION_CLICK, kiUp_action);
    lv_btn_set_action(kiDown, LV_BTN_ACTION_CLICK, kiDown_action);
    lv_btn_set_action(kdUp, LV_BTN_ACTION_CLICK, kdUp_action);
    lv_btn_set_action(kdDown, LV_BTN_ACTION_CLICK, kdDown_action);

    //create k value labels
    kp = lv_label_create(settingsScr, NULL);
    ki = lv_label_create(settingsScr, NULL);
    kd = lv_label_create(settingsScr, NULL);

    //assign PID values to k labels
    getPIDvalues();
    
}