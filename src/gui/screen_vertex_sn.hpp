#pragma once

#include "gui.hpp"
#include "window_header.hpp"
#include "status_footer.h"
#include "window_text.hpp"
#include "window_icon.hpp"
#include "ScreenFactory.hpp"
#include "screen.hpp"
#include "support_utils.h" //MAX_LEN_4QR

struct ScreenVertexSN : public AddSuperWindow<screen_t> {
    ScreenVertexSN();

private:
    window_header_t header;
    status_footer_t footer;
    window_text_button_t button_ok;
    window_text_button_t button_cancel;
    window_text_t text_title;
    window_text_t text_description;
    window_text_t text_info;
};
