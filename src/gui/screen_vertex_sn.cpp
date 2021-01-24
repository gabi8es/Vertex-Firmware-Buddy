#include "ScreenHandler.hpp"
#include "screen_vertex_sn.hpp"
#include "display.h"
#include "resource.h"
#include "st25dv64k.h"

static const constexpr uint32_t OTP_START_ADDR = 0x1FFF7800;
static const constexpr uint32_t SERIAL_NUM_ADDR = 0x1FFF7808;
static const constexpr uint8_t VERSION_INFO_STR_MAXLEN = 150;
static const char title[] = "Set the S/N";
static const char description[] = "Warning! You will set/change your S/N, your waranty will be avoided, follow under your own risk.";
static const char info[] = "vertex3d.org";

//constexpr static const HelperConfig HelpCfg = { 10, IDR_FNT_NORMAL };
static void onclick_ok();
static void onclick_cancel();
//using Screen = ScreenMenu<EHeader::Off, EFooter::On, HelpLines_None, MI_RETURN>;
//display::Clear(COLOR_RED_ALERT);
//GuiDefaults::Font, COLOR_RED_ALERT, COLOR_WHITE);

/*class ScreenVertexSN : public Screen {
public:
    // std::array<char, VERSION_INFO_STR_MAXLEN> version_info_str;
    constexpr static const char *label = N_("Set Serial Number");
    ScreenVertexSN();
};*/

ScreenVertexSN::ScreenVertexSN()
    : AddSuperWindow<screen_t>()
    , header(this)
    , footer(this)
    , text_title(this, Rect16(8, 55, 224, 25), is_multiline::no)
    , text_description(this, Rect16(8, 85, 224, 125), is_multiline::yes)
    , text_info(this, Rect16(8, 210, 224, 20), is_multiline::no)
    , button_ok(this, Rect16(40, 235, 80, 20), onclick_ok, _("OK"))
    , button_cancel(this, Rect16(140, 235, 80, 20), onclick_cancel, _("CANCEL"))
    {
    header.SetText(_("VERTEX"));
    text_title.SetBackColor(COLOR_RED_ALERT);
    text_title.SetAlignment(ALIGN_CENTER);
    text_title.font = resource_font(IDR_FNT_BIG);
    text_title.SetText(string_view_utf8::MakeCPUFLASH((const uint8_t *)title));

    text_description.SetBackColor(COLOR_RED_ALERT);
    text_description.SetText(string_view_utf8::MakeCPUFLASH((const uint8_t *)description));

    text_info.SetBackColor(COLOR_RED_ALERT);
    text_info.SetAlignment(ALIGN_CENTER);
    text_info.SetText(string_view_utf8::MakeCPUFLASH((const uint8_t *)info));

    button_cancel.SetFocus();
}

void set_serial_number(){
    char VertexSN[15] = "VTX40517300721";
    VertexSN[14] = '\0';

    st25dv64k_user_write_bytes_32(SERIAL_NUM_ADDR, &VertexSN, sizeof(VertexSN));
}

void onclick_ok() {
    ///TODO: store count changed characters
    ///uint32_t cnt = sheet_rename(
   //  _dbg("Rename Cnt: %d\n", sheet_rename(screen_sheet_rename_t::index_, "anything", 8));
    Screens::Access()->Close();
}

void onclick_cancel() {
    Screens::Access()->Close();
}


ScreenFactory::UniquePtr GetScreenVertexSN() {
    return ScreenFactory::Screen<ScreenVertexSN>();
}
