#include <iostream>

#include "UiBoard.h"
#include "Tile.h"
#include "lvgl/lvgl.h"

#define GRID_SIZE 10
#define CELL_SIZE 20


static lv_style_t style_btn;
static lv_style_t style_button_pressed;
static lv_style_t style_button_red;

static lv_color_t darken(const lv_color_filter_dsc_t * dsc, lv_color_t color, lv_opa_t opa)
{
    LV_UNUSED(dsc);
    return lv_color_darken(color, opa);
}


static void event_cb(lv_event_t * e)
{
      /*The original target of the event. Can be the buttons or the container*/
    lv_obj_t * btn = static_cast<lv_obj_t *>(lv_event_get_target(e));

    // lv_obj_t * label = lv_obj_get_child(btn, 0);
    // lv_label_set_text_fmt(label, "%"LV_PRIu32, cnt);

    /*Make the clicked buttons red*/
    lv_obj_set_style_bg_color(btn, lv_palette_main(LV_PALETTE_RED), 0);
}


UiBoard::UiBoard()
{

}

void UiBoard::Initialize(lv_obj_t *parent)
{
    static int32_t col_dsc[] = {CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, 200, 200);
    lv_obj_center(cont);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);

    lv_obj_set_style_pad_row(cont, 0, 0);
    lv_obj_set_style_pad_column(cont, 0, 0);

    lv_obj_t * label;
    lv_obj_t * btn;

    uint32_t i;
    for(i = 0; i < GRID_SIZE * GRID_SIZE; i++)
    {
        uint8_t col = i % GRID_SIZE;
        uint8_t row = i / GRID_SIZE;

        btn = lv_button_create(cont);

        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_remove_style_all(btn);
        lv_obj_set_size(btn, 20, 20);
        lv_obj_add_style(btn, &style_btn, 0);
        lv_obj_add_style(btn, &style_button_pressed, LV_STATE_PRESSED);

        /*Stretch the cell horizontally and vertically too
         *Set span to 1 to make the cell 1 column/row sized*/
        lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_START, col, 1,
                             LV_GRID_ALIGN_START, row, 1);

        label = lv_label_create(btn);
        lv_label_set_text_fmt(label, " ");
        lv_obj_center(label);
    }
}

void UiBoard::Update(IBoard &board)
{
    board.Accept(*this);
}


void UiBoard::Visit(const Tile &tile)
{
    std::cout << "State: " << (int)tile.GetState();
}

void UiBoard::StyleInit(void)
{
    /*Create a simple button style*/
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 0);
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn, lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 3));
    // lv_style_set_bg_grad_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
    // lv_style_set_bg_grad_dir(&style_btn, LV_GRAD_DIR_VER);

    lv_style_set_border_color(&style_btn, lv_color_black());
    lv_style_set_border_opa(&style_btn, LV_OPA_20);
    lv_style_set_border_width(&style_btn, 2);

    lv_style_set_text_color(&style_btn, lv_color_black());

    /*Create a style for the pressed state.
     *Use a color filter to simply modify all colors in this state*/
    static lv_color_filter_dsc_t color_filter;
    lv_color_filter_dsc_init(&color_filter, darken);
    lv_style_init(&style_button_pressed);
    lv_style_set_color_filter_dsc(&style_button_pressed, &color_filter);
    lv_style_set_color_filter_opa(&style_button_pressed, LV_OPA_20);

    /*Create a red style. Change only some colors.*/
    lv_style_init(&style_button_red);
    lv_style_set_bg_color(&style_button_red, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_button_red, lv_palette_lighten(LV_PALETTE_RED, 3));
}
