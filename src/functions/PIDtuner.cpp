#include "display/lv_core/lv_obj.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_label.h"
#include "main.h"

const int buttonSize = 50;

static lv_obj_t* kp;
static lv_obj_t* ki;
static lv_obj_t* kd;


static void getPIDvalues(void) {
    static char buffer[32];
    snprintf(buffer, 32, "kP: %.2f", kP);
    lv_label_set_text(kp, buffer);

    static char otherBuffer[32];
    snprintf(otherBuffer, 32, "kI: %.2f", kI);
    lv_label_set_text(ki, otherBuffer);

    static char notOtherBuffer[32];
    snprintf(notOtherBuffer, 32, "kD: %.2f", kD);
    lv_label_set_text(kd, notOtherBuffer);
}

static lv_res_t kpUp_action(lv_obj_t* btn) {
    kP += .05;
    getPIDvalues();

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kpDown_action(lv_obj_t* btn) {
    kP -= .05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kiUp_action(lv_obj_t* btn) {
    kI += .05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kiDown_action(lv_obj_t* btn) {
    kI -= .05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kdUp_action(lv_obj_t* btn) {
    kD += .05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t kdDown_action(lv_obj_t* btn) {
    kD -= .05;
    getPIDvalues();
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void PIDtuner(void) {
    //480 x 240 pixels

    /*Create a style for all objects*/
    static lv_style_t tunerStyle;
    lv_style_copy(&tunerStyle, &lv_style_plain);
    tunerStyle.body.main_color = LV_COLOR_ORANGE;
    tunerStyle.body.grad_color = LV_COLOR_ORANGE;
    tunerStyle.text.color = LV_COLOR_WHITE;

    /*Create a screen to store PID settings objects*/
    lv_obj_t* settingsScr = lv_obj_create(NULL, NULL);
    lv_obj_set_style(settingsScr, &tunerStyle);

    lv_scr_load(settingsScr);

    /*Create and align a title called "Settings"*/
    lv_obj_t* settingsTitle = lv_label_create(settingsScr, NULL);
    lv_label_set_text(settingsTitle, "Settings");
    lv_label_set_align(settingsTitle, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(settingsTitle, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

    /*Create buttons to change PID k values*/
    lv_obj_t* kpUp = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kpDown = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kiUp = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kiDown = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kdUp = lv_btn_create(settingsScr, NULL);
    lv_obj_t* kdDown = lv_btn_create(settingsScr, NULL);
    lv_obj_align(kpUp, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    lv_obj_align(kpDown, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    lv_obj_align(kiUp, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_align(kiDown, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_align(kdUp, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
    lv_obj_align(kdDown, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);

    /*Set size for setting buttons*/
    lv_obj_set_size(kpUp, buttonSize, buttonSize);
    lv_obj_set_size(kpDown, buttonSize, buttonSize);
    lv_obj_set_size(kiUp, buttonSize, buttonSize);
    lv_obj_set_size(kiDown, buttonSize, buttonSize);
    lv_obj_set_size(kdUp, buttonSize, buttonSize);
    lv_obj_set_size(kdDown, buttonSize, buttonSize);


    /*Create labels for buttons to change PID k values*/
    lv_obj_t* kpUpLabel = lv_label_create(kpUp, NULL);
    lv_obj_t* kpDownLabel = lv_label_create(kpDown, NULL);
    lv_obj_t* kiUpLabel = lv_label_create(kiUp, NULL);
    lv_obj_t* kiDownLabel = lv_label_create(kiDown, NULL);
    lv_obj_t* kdUpLabel = lv_label_create(kdUp, NULL);
    lv_obj_t* kdDownLabel = lv_label_create(kdDown, NULL);


    /*Set k Button label values*/
    lv_label_set_text(kpUpLabel, "+kP");
    lv_label_set_text(kiUpLabel, "+kI");
    lv_label_set_text(kdUpLabel, "+kD");
    lv_label_set_text(kpDownLabel, "-kP");
    lv_label_set_text(kiDownLabel, "-kI");
    lv_label_set_text(kdDownLabel, "-kD");

    /*Align labels on setting buttons to center*/
    lv_label_set_align(kpUpLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_align(kiUpLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_align(kdUpLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_align(kpDownLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_align(kiDownLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_align(kdDownLabel, LV_LABEL_ALIGN_CENTER);

    /*Set actions for k setting buttons*/
    lv_btn_set_action(kpUp, LV_BTN_ACTION_CLICK, kpUp_action);
    lv_btn_set_action(kpDown, LV_BTN_ACTION_CLICK, kpDown_action);
    lv_btn_set_action(kiUp, LV_BTN_ACTION_CLICK, kiUp_action);
    lv_btn_set_action(kiDown, LV_BTN_ACTION_CLICK, kiDown_action);
    lv_btn_set_action(kdUp, LV_BTN_ACTION_CLICK, kdUp_action);
    lv_btn_set_action(kdDown, LV_BTN_ACTION_CLICK, kdDown_action);

    /*Create labels to display current k values*/
    kp = lv_label_create(settingsScr, NULL);
    ki = lv_label_create(settingsScr, NULL);
    kd = lv_label_create(settingsScr, NULL);
    lv_obj_align(kp, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 5);
    lv_obj_align(ki, kp, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_align(kd, ki, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    /*Create button to run PID test*/
    lv_obj_t* runButton = lv_btn_create(settingsScr, NULL);
    lv_obj_align(runButton, NULL, LV_ALIGN_CENTER, 0, 0);

    /*Update k values on display*/
    getPIDvalues();

}