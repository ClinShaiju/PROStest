#include "PIDtuner.hpp"

const int buttonSize = 50;

static lv_obj_t* kp;
static lv_obj_t* ki;
static lv_obj_t* kd;
static lv_obj_t* motorPower;


//screens
lv_obj_t* settingsScr;
lv_obj_t* PIDrunning;
lv_obj_t* graph;

lv_obj_t* chart;
lv_chart_series_t * leftY;
lv_chart_series_t * leftX;
lv_chart_series_t * rightY;
lv_chart_series_t * rightX;


void my_task(void*)
{
  /*Use the user_data*/
    lv_chart_set_point_count(chart, 750);
    lv_chart_set_next(chart, leftY, controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    lv_chart_set_next(chart, leftX, controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
    lv_chart_set_next(chart, rightY, controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    lv_chart_set_next(chart, rightX, controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

    static char theOtherBuffer[32];
    snprintf(theOtherBuffer, 32, "Power: %.2f %d %d", averagePosition, leftPos(), rightPos());
    lv_label_set_text(motorPower, theOtherBuffer);


  /*Do something with LittlevGL*/

}

static void getPIDvalues(void) {
    static char buffer[32];
    snprintf(buffer, 32, "%.2f", kP);
    lv_label_set_text(kp, buffer);

    static char otherBuffer[32];
    snprintf(otherBuffer, 32, "%.2f", kI);
    lv_label_set_text(ki, otherBuffer);

    static char notOtherBuffer[32];
    snprintf(notOtherBuffer, 32, "%.2f", kD);
    lv_label_set_text(kd, notOtherBuffer);
}

static lv_res_t stopPID(lv_obj_t* btn) {
    enableDrivePID = false;
    lv_scr_load(settingsScr);
    desiredValue = 0;
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t startPID(lv_obj_t* btn) {
    resetDriveSensors = true;
    enableDrivePID = true;
    desiredValue = 30000;
    lv_scr_load(PIDrunning);
    return LV_RES_OK; /*Return OK if the button is not deleted*/
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
    tunerStyle.body.main_color = LV_COLOR_HEX(0x520031);
    tunerStyle.body.grad_color = LV_COLOR_HEX(0x520031);
    tunerStyle.text.color = LV_COLOR_WHITE;

    static lv_style_t tunerBtnRelStyle;
    lv_style_copy(&tunerBtnRelStyle, &tunerStyle);
    tunerBtnRelStyle.body.main_color = LV_COLOR_HEX(0xa80054);
    tunerBtnRelStyle.body.grad_color = LV_COLOR_HEX(0xa80054);
    tunerBtnRelStyle.body.radius = 5;
    tunerBtnRelStyle.body.border.color = LV_COLOR_WHITE;
    tunerBtnRelStyle.body.border.width = 3;

    static lv_style_t tunerBtnPressStyle;
    lv_style_copy(&tunerBtnPressStyle, &tunerBtnRelStyle);
    tunerBtnPressStyle.body.main_color = LV_COLOR_GRAY;
    tunerBtnPressStyle.body.grad_color = LV_COLOR_GRAY;

    /*Create a screen to store PID settings objects*/
    settingsScr = lv_obj_create(NULL, NULL);
    lv_obj_set_style(settingsScr, &tunerStyle);

    lv_scr_load(settingsScr);

    /*Create container to hold title section*/
    lv_obj_t* titleContainer = lv_obj_create(settingsScr, NULL);
    lv_obj_align(titleContainer, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_obj_set_size(titleContainer, 480, 20);

    /*Create and align a title called "Settings"*/
    lv_obj_t* settingsTitle = lv_label_create(titleContainer, NULL);
    lv_label_set_text(settingsTitle, "Settings");
    lv_obj_align(settingsTitle, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* kSettingCont = lv_obj_create(settingsScr, NULL);
    lv_obj_set_size(kSettingCont, 480, 100);
    lv_obj_align(kSettingCont, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    lv_obj_t* kPCont = lv_obj_create(kSettingCont, NULL);
    lv_obj_set_size(kPCont, 50, 100);
    lv_obj_align(kPCont, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);

    lv_obj_t* kICont = lv_obj_create(kSettingCont, NULL);
    lv_obj_set_size(kICont, 50, 100);
    lv_obj_align(kICont, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* kDCont = lv_obj_create(kSettingCont, NULL);
    lv_obj_set_size(kDCont, 50, 100);
    lv_obj_align(kDCont, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_style(kPCont, &tunerStyle);
    lv_obj_set_style(kICont, &tunerStyle);
    lv_obj_set_style(kDCont, &tunerStyle);


    /*Create buttons to change PID k values*/
    lv_obj_t* kpUp = lv_btn_create(kPCont, NULL);
    lv_obj_t* kpDown = lv_btn_create(kPCont, NULL);
    lv_obj_t* kiUp = lv_btn_create(kICont, NULL);
    lv_obj_t* kiDown = lv_btn_create(kICont, NULL);
    lv_obj_t* kdUp = lv_btn_create(kDCont, NULL);
    lv_obj_t* kdDown = lv_btn_create(kDCont, NULL);

    /*Set size for setting buttons*/
    lv_obj_set_size(kpUp, buttonSize, 35);
    lv_obj_set_size(kpDown, buttonSize, 35);
    lv_obj_set_size(kiUp, buttonSize, 35);
    lv_obj_set_size(kiDown, buttonSize, 35);
    lv_obj_set_size(kdUp, buttonSize, 35);
    lv_obj_set_size(kdDown, buttonSize, 35);
    /*Align k setting buttons*/
    lv_obj_align(kpUp, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_align(kpDown, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_align(kiUp, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_align(kiDown, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_align(kdUp, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_align(kdDown, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);




    /*Create labels for buttons to change PID k values*/
    lv_obj_t* kpUpLabel = lv_label_create(kpUp, NULL);
    lv_obj_t* kpDownLabel = lv_label_create(kpDown, NULL);
    lv_obj_t* kiUpLabel = lv_label_create(kiUp, NULL);
    lv_obj_t* kiDownLabel = lv_label_create(kiDown, NULL);
    lv_obj_t* kdUpLabel = lv_label_create(kdUp, NULL);
    lv_obj_t* kdDownLabel = lv_label_create(kdDown, NULL);


    /*Set k Button label values*/
    lv_label_set_text(kpUpLabel, "+P");
    lv_label_set_text(kiUpLabel, "+I");
    lv_label_set_text(kdUpLabel, "+D");
    lv_label_set_text(kpDownLabel, "-P");
    lv_label_set_text(kiDownLabel, "-I");
    lv_label_set_text(kdDownLabel, "-D");

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
    kp = lv_label_create(kPCont, NULL);
    ki = lv_label_create(kICont, NULL);
    kd = lv_label_create(kDCont, NULL);
    lv_obj_align(kp, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(ki, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(kd, NULL, LV_ALIGN_CENTER, 0, 0);

    /*Create body container*/
    lv_obj_t* bodyCont = lv_obj_create(settingsScr, NULL);
    lv_obj_set_size(bodyCont, 480, 120);
    lv_obj_align(bodyCont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 20);


    /*Create button to run PID test*/
    lv_obj_t* runPIDButton = lv_btn_create(bodyCont, NULL);
    lv_obj_align(runPIDButton, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* runLabel = lv_label_create(runPIDButton, NULL);
    lv_label_set_text(runLabel, "RUN");
    lv_label_set_align(runPIDButton,LV_ALIGN_CENTER);

    /*Add PID functionality to RUN button*/
    lv_btn_set_action(runPIDButton, LV_BTN_ACTION_CLICK, startPID);


    /*Update k values on display*/
    getPIDvalues();

    /*Create screen for when PID is running*/
    PIDrunning = lv_obj_create(NULL, NULL);

     /*Create button to stop PID test*/
    lv_obj_t* stopPIDButton = lv_btn_create(PIDrunning, NULL);
    lv_obj_align(stopPIDButton, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* stopPIDLabel = lv_label_create(stopPIDButton, NULL);
    lv_label_set_text(stopPIDLabel, "STOP TEST");
    lv_label_set_align(stopPIDButton,LV_ALIGN_CENTER);

    /*Add PID functionality to STOP button*/
    lv_btn_set_action(stopPIDButton, LV_BTN_ACTION_CLICK, stopPID);

    

    graph = lv_obj_create(NULL, NULL);
    chart = lv_chart_create(graph, NULL);
    lv_obj_align(chart, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_obj_set_size(chart, 480, 240);
    leftY = lv_chart_add_series(chart, LV_COLOR_RED);
    leftX = lv_chart_add_series(chart, LV_COLOR_GREEN);
    rightX = lv_chart_add_series(chart, LV_COLOR_YELLOW);
    rightY = lv_chart_add_series(chart, LV_COLOR_BLUE);
    lv_chart_set_range(chart, -100, 100);

    lv_scr_load(settingsScr);

    lv_task_t * task = lv_task_create(my_task, 20, LV_TASK_PRIO_MID, nullptr);

    motorPower = lv_label_create(PIDrunning, NULL);

    lv_obj_set_style(PIDrunning, &tunerStyle);
    lv_obj_set_style(titleContainer, &tunerStyle);
    lv_obj_set_style(bodyCont, &tunerStyle);
    lv_obj_set_style(kSettingCont, &tunerStyle);
    lv_obj_set_style(kPCont, &tunerStyle);
    lv_obj_set_style(kICont, &tunerStyle);
    lv_obj_set_style(kDCont, &tunerStyle);
    lv_obj_set_style(settingsTitle, &tunerStyle);
    lv_obj_set_style(kpUpLabel, &tunerStyle);
    lv_obj_set_style(kpDownLabel, &tunerStyle);
    lv_obj_set_style(kiUpLabel, &tunerStyle);
    lv_obj_set_style(kiDownLabel, &tunerStyle);
    lv_obj_set_style(kdDownLabel, &tunerStyle);
    lv_obj_set_style(kdUpLabel, &tunerStyle);

    lv_btn_set_style(runPIDButton, LV_BTN_STYLE_REL, &tunerBtnRelStyle);
    lv_btn_set_style(kpUp, LV_BTN_STYLE_REL, &tunerBtnRelStyle);
    lv_btn_set_style(kpDown, LV_BTN_STYLE_REL, &tunerBtnRelStyle);
    lv_btn_set_style(kiUp, LV_BTN_STYLE_REL, &tunerBtnRelStyle);
    lv_btn_set_style(kiDown, LV_BTN_STYLE_REL, &tunerBtnRelStyle);
    lv_btn_set_style(kdDown, LV_BTN_STYLE_REL, &tunerBtnRelStyle);
    lv_btn_set_style(kdUp, LV_BTN_STYLE_REL, &tunerBtnRelStyle);
    lv_btn_set_style(stopPIDButton, LV_BTN_STYLE_REL, &tunerBtnRelStyle);

    lv_btn_set_style(runPIDButton, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    lv_btn_set_style(kpUp, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    lv_btn_set_style(kpDown, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    lv_btn_set_style(kiUp, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    lv_btn_set_style(kiDown, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    lv_btn_set_style(kdDown, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    lv_btn_set_style(kdUp, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    lv_btn_set_style(stopPIDButton, LV_BTN_STYLE_PR, &tunerBtnPressStyle);
    


}