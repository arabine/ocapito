#pragma once

#include <vector>

#include "IBoard.h"
#include "IBoardVisitor.h"
#include "lvgl/lvgl.h"

class UiBoard : public IBoardVisitor
{
public:
    UiBoard();

    void Initialize(lv_obj_t *parent);

    static void StyleInit();


    void Update(IBoard &board);

    // From ITileVisitor
    virtual void Visit(const Tile &tile);


private:
    std::vector<lv_obj_t *> m_grid;
};
