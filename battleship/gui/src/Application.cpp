#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"
#include "glob.h"

#include "UiBoard.h"
#include "Application.h"




/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t * hal_init(int32_t w, int32_t h)
{

  lv_group_set_default(lv_group_create());

  lv_display_t * disp = lv_sdl_window_create(w, h);

  lv_indev_t * mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj;
  cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

  lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);
  lv_indev_set_group(mousewheel, lv_group_get_default());

  lv_indev_t * kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());

  return disp;
}

void Application::Initialize()
{
    // Initialize LVGL
    lv_init();

    // Initialize the HAL (display, input devices, tick) for LVGL
    hal_init(480, 600);

    LV_IMAGE_DECLARE(logo);

    UiBoard::StyleInit();

    auto parent  = lv_screen_active();
    // Récupère la largeur et hauteur de l'écran
    lv_coord_t screen_width = lv_obj_get_width(parent);

    // Logo
    lv_obj_t * img = lv_image_create(parent);

    lv_image_set_src(img, &logo);
    lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 0);

    // Barre du bas
    CreateBottomBar();

    // Initialisation des grilles de jeu dans un conteneur
    lv_obj_t *gridsRow = lv_obj_create(lv_screen_active());
    lv_obj_set_size(gridsRow, screen_width - 10, 210);
    lv_obj_set_y(gridsRow, 50);
    lv_obj_set_flex_flow(gridsRow, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(gridsRow, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    m_boatsGrid.Initialize(gridsRow);
    m_shotsGrid.Initialize(gridsRow);
}

void Application::CreateBottomBar()
{
    auto parent  = lv_screen_active();
    // Récupère la largeur et hauteur de l'écran
    lv_coord_t screen_width = lv_obj_get_width(parent);
    // lv_coord_t screen_height = lv_obj_get_height(parent);

    // Crée un conteneur pour la barre d'icônes
    lv_obj_t *icon_bar = lv_obj_create(parent);
    lv_obj_set_size(icon_bar, screen_width, 50); // Barre de 50px de hauteur
    lv_obj_align(icon_bar, LV_ALIGN_BOTTOM_MID, 0, 0); // Collée en bas
    lv_obj_set_style_bg_color(icon_bar, lv_color_hex(0x333333), LV_PART_MAIN); // Couleur de fond de la barre

    // Paramètre pour l'alignement des icônes dans la barre
    lv_obj_set_flex_flow(icon_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(icon_bar, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);


    static const char * symbols[] = { LV_SYMBOL_HOME, LV_SYMBOL_PLAY, LV_SYMBOL_STOP};

    // Ajout de trois boutons icônes dans la barre
    for (int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_btn_create(icon_bar);
        lv_obj_set_size(btn, 40, 40); // Taille de chaque icône

        // Création de l'icône
        lv_obj_t *icon = lv_label_create(btn);
        lv_label_set_text(icon, symbols[i]); // Icônes par défaut, modifiez selon vos besoins
        lv_obj_center(icon);
    }



}


void Application::Loop()
{
  while(1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    usleep(5 * 1000);
  }

}
