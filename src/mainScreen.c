#include "lvgl.h"

void hakunamatata(void);
static void createSettingTab(lv_obj_t *parent);
static void createMainTab(lv_obj_t *parent);
static void chart_event_cb(lv_event_t *e);

static lv_obj_t *chart1;
static lv_style_t style_title;
static lv_chart_series_t *ser1;
static lv_obj_t *list;
static lv_obj_t *btn;

void addBtn(lv_obj_t *parent, char *labelText);
static void list_event_handler(lv_event_t *e);

void hakunamatata()
{
    static lv_obj_t *tv;

    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_TEAL), lv_palette_main(LV_PALETTE_AMBER), LV_THEME_DEFAULT_DARK,
                          &lv_font_montserrat_14);

    tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 45);
    lv_obj_t *t1 = lv_tabview_add_tab(tv, "Haku");
    lv_obj_t *t2 = lv_tabview_add_tab(tv, "Nama");
    lv_obj_t *t3 = lv_tabview_add_tab(tv, "Tata");
    createMainTab(t1);
    createSettingTab(t2);
}
static void createSettingTab(lv_obj_t *parent)
{
    list = lv_list_create(parent);
    lv_obj_set_size(list, LV_PCT(100), LV_PCT(100));

    btn = lv_list_add_btn(list, LV_SYMBOL_HOME, "Home");
    lv_obj_add_event_cb(btn, list_event_handler, LV_EVENT_CLICKED, NULL);
    lv_list_add_text(list, "Settings");

    btn = lv_list_add_btn(list, LV_SYMBOL_SETTINGS, "General");
    lv_obj_add_event_cb(btn, list_event_handler, LV_EVENT_CLICKED, NULL);

    lv_list_add_text(list, "Connectivity");
    btn = lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    lv_obj_add_event_cb(btn, list_event_handler, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");
    lv_obj_add_event_cb(btn, list_event_handler, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list, LV_SYMBOL_USB, "USB");
    lv_obj_add_event_cb(btn, list_event_handler, LV_EVENT_CLICKED, NULL);
    lv_list_add_text(list, "Utility");
    btn = lv_list_add_btn(list, LV_SYMBOL_BATTERY_FULL, "Battery");
    lv_obj_add_event_cb(btn, list_event_handler, LV_EVENT_CLICKED, NULL);
}
static void createMainTab(lv_obj_t *parent)
{

    // styles
    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, &lv_font_montserrat_18);

    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    static lv_coord_t grid_chart_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_FR(1), 10, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t grid_chart_col_dsc[] = {20, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_t *chart1_cont = lv_obj_create(parent);
    lv_obj_set_flex_grow(chart1_cont, 1);
    lv_obj_set_grid_dsc_array(chart1_cont, grid_chart_col_dsc, grid_chart_row_dsc);

    lv_obj_set_height(chart1_cont, LV_PCT(100));
    lv_obj_set_width(chart1_cont, LV_PCT(100));
    lv_obj_set_style_max_height(chart1_cont, 180, 0);
    lv_obj_set_style_min_height(chart1_cont, 180, 0);

    lv_obj_t *title = lv_label_create(chart1_cont);
    lv_label_set_text(title, "Dummy Line graph");
    lv_obj_add_style(title, &style_title, 0);
    lv_obj_set_grid_cell(title, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_START, 0, 1);

    chart1 = lv_chart_create(chart1_cont);
    lv_group_add_obj(lv_group_get_default(), chart1);
    lv_obj_add_flag(chart1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_set_grid_cell(chart1, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 0, 5, 1, true, 80);
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_X, 0, 0, 12, 1, true, 50);
    lv_chart_set_div_line_count(chart1, 0, 12);
    lv_chart_set_point_count(chart1, 12);
    lv_obj_add_event_cb(chart1, chart_event_cb, LV_EVENT_ALL, NULL);
    lv_chart_set_zoom_x(chart1, 256);

    lv_obj_set_style_border_side(chart1, LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_radius(chart1, 0, 0);

    ser1 = lv_chart_add_series(chart1, lv_theme_get_color_primary(chart1), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
}

static void list_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: %s", lv_list_get_btn_text(list1, obj));
    }
}

static void chart_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_PRESSED || code == LV_EVENT_RELEASED)
    {
        lv_obj_invalidate(obj); /*To make the value boxes visible*/
    }
}

void addBtn(lv_obj_t *parent, char *labelText)
{
    lv_obj_t *label;
    lv_obj_t *btn = lv_btn_create(parent);
    // lv_obj_add_event_cb(btn, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, -40);
    label = lv_label_create(btn);
    lv_label_set_text(label, labelText);
    lv_obj_center(label);
}