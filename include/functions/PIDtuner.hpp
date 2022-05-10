#include "main.h"

//GUI Application
void PIDtuner(void);

static void getPIDvalues(void);

static lv_res_t kpUp_action(lv_obj_t * btn);
static lv_res_t kpDown_action(lv_obj_t * btn);
static lv_res_t kiUp_action(lv_obj_t * btn);
static lv_res_t kiDown_action(lv_obj_t * btn);
static lv_res_t kdUp_action(lv_obj_t * btn);
static lv_res_t kdDown_action(lv_obj_t * btn);