/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Controls 2 module of Qt).
**
** QtCellink is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef MATERIAL_H
#define MATERIAL_H

#include <QtCore/qobject.h>
#include <QtGui/qcolor.h>

class Material : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor red READ red NOTIFY changed)
    Q_PROPERTY(QColor pink READ pink NOTIFY changed)
    Q_PROPERTY(QColor purple READ purple NOTIFY changed)
    Q_PROPERTY(QColor deepPurple READ deepPurple NOTIFY changed)
    Q_PROPERTY(QColor indigo READ indigo NOTIFY changed)
    Q_PROPERTY(QColor blue READ blue NOTIFY changed)
    Q_PROPERTY(QColor lightBlue READ lightBlue NOTIFY changed)
    Q_PROPERTY(QColor cyan READ cyan NOTIFY changed)
    Q_PROPERTY(QColor teal READ teal NOTIFY changed)
    Q_PROPERTY(QColor green READ green NOTIFY changed)
    Q_PROPERTY(QColor lightGreen READ lightGreen NOTIFY changed)
    Q_PROPERTY(QColor lime READ lime NOTIFY changed)
    Q_PROPERTY(QColor yellow READ yellow NOTIFY changed)
    Q_PROPERTY(QColor amber READ amber NOTIFY changed)
    Q_PROPERTY(QColor orange READ orange NOTIFY changed)
    Q_PROPERTY(QColor deepOrange READ deepOrange NOTIFY changed)
    Q_PROPERTY(QColor brown READ brown NOTIFY changed)
    Q_PROPERTY(QColor gray READ gray NOTIFY changed)
    Q_PROPERTY(QColor blueGray READ blueGray NOTIFY changed)
    Q_PROPERTY(Shade shade READ shade WRITE setShade NOTIFY changed)

    Q_PROPERTY(QString fontFamily READ fontFamily CONSTANT)
    Q_PROPERTY(QString _10k READ _10k CONSTANT)
    Q_PROPERTY(QString _10mp READ _10mp CONSTANT)
    Q_PROPERTY(QString _11mp READ _11mp CONSTANT)
    Q_PROPERTY(QString _12mp READ _12mp CONSTANT)
    Q_PROPERTY(QString _13mp READ _13mp CONSTANT)
    Q_PROPERTY(QString _14mp READ _14mp CONSTANT)
    Q_PROPERTY(QString _15mp READ _15mp CONSTANT)
    Q_PROPERTY(QString _16mp READ _16mp CONSTANT)
    Q_PROPERTY(QString _17mp READ _17mp CONSTANT)
    Q_PROPERTY(QString _18mp READ _18mp CONSTANT)
    Q_PROPERTY(QString _19mp READ _19mp CONSTANT)
    Q_PROPERTY(QString _1k READ _1k CONSTANT)
    Q_PROPERTY(QString _1k_plus READ _1k_plus CONSTANT)
    Q_PROPERTY(QString _20mp READ _20mp CONSTANT)
    Q_PROPERTY(QString _21mp READ _21mp CONSTANT)
    Q_PROPERTY(QString _22mp READ _22mp CONSTANT)
    Q_PROPERTY(QString _23mp READ _23mp CONSTANT)
    Q_PROPERTY(QString _24mp READ _24mp CONSTANT)
    Q_PROPERTY(QString _2k READ _2k CONSTANT)
    Q_PROPERTY(QString _2k_plus READ _2k_plus CONSTANT)
    Q_PROPERTY(QString _2mp READ _2mp CONSTANT)
    Q_PROPERTY(QString _360 READ _360 CONSTANT)
    Q_PROPERTY(QString _3d_rotation READ _3d_rotation CONSTANT)
    Q_PROPERTY(QString _3k READ _3k CONSTANT)
    Q_PROPERTY(QString _3k_plus READ _3k_plus CONSTANT)
    Q_PROPERTY(QString _3mp READ _3mp CONSTANT)
    Q_PROPERTY(QString _4k READ _4k CONSTANT)
    Q_PROPERTY(QString _4k_plus READ _4k_plus CONSTANT)
    Q_PROPERTY(QString _4mp READ _4mp CONSTANT)
    Q_PROPERTY(QString _5k READ _5k CONSTANT)
    Q_PROPERTY(QString _5k_plus READ _5k_plus CONSTANT)
    Q_PROPERTY(QString _5mp READ _5mp CONSTANT)
    Q_PROPERTY(QString _6k READ _6k CONSTANT)
    Q_PROPERTY(QString _6k_plus READ _6k_plus CONSTANT)
    Q_PROPERTY(QString _6mp READ _6mp CONSTANT)
    Q_PROPERTY(QString _7k READ _7k CONSTANT)
    Q_PROPERTY(QString _7k_plus READ _7k_plus CONSTANT)
    Q_PROPERTY(QString _7mp READ _7mp CONSTANT)
    Q_PROPERTY(QString _8k READ _8k CONSTANT)
    Q_PROPERTY(QString _8k_plus READ _8k_plus CONSTANT)
    Q_PROPERTY(QString _8mp READ _8mp CONSTANT)
    Q_PROPERTY(QString _9k READ _9k CONSTANT)
    Q_PROPERTY(QString _9k_plus READ _9k_plus CONSTANT)
    Q_PROPERTY(QString _9mp READ _9mp CONSTANT)
    Q_PROPERTY(QString _class READ _class CONSTANT)
    Q_PROPERTY(QString _delete READ _delete CONSTANT)
    Q_PROPERTY(QString _explicit READ _explicit CONSTANT)
    Q_PROPERTY(QString _public READ _public CONSTANT)
    Q_PROPERTY(QString ac_unit READ ac_unit CONSTANT)
    Q_PROPERTY(QString access_alarm READ access_alarm CONSTANT)
    Q_PROPERTY(QString access_alarms READ access_alarms CONSTANT)
    Q_PROPERTY(QString access_time READ access_time CONSTANT)
    Q_PROPERTY(QString accessibility READ accessibility CONSTANT)
    Q_PROPERTY(QString accessibility_new READ accessibility_new CONSTANT)
    Q_PROPERTY(QString accessible READ accessible CONSTANT)
    Q_PROPERTY(QString accessible_forward READ accessible_forward CONSTANT)
    Q_PROPERTY(QString account_balance READ account_balance CONSTANT)
    Q_PROPERTY(QString account_balance_wallet READ account_balance_wallet CONSTANT)
    Q_PROPERTY(QString account_box READ account_box CONSTANT)
    Q_PROPERTY(QString account_circle READ account_circle CONSTANT)
    Q_PROPERTY(QString account_tree READ account_tree CONSTANT)
    Q_PROPERTY(QString adb READ adb CONSTANT)
    Q_PROPERTY(QString add READ add CONSTANT)
    Q_PROPERTY(QString add_a_photo READ add_a_photo CONSTANT)
    Q_PROPERTY(QString add_alarm READ add_alarm CONSTANT)
    Q_PROPERTY(QString add_alert READ add_alert CONSTANT)
    Q_PROPERTY(QString add_box READ add_box CONSTANT)
    Q_PROPERTY(QString add_call READ add_call CONSTANT)
    Q_PROPERTY(QString add_chart READ add_chart CONSTANT)
    Q_PROPERTY(QString add_circle READ add_circle CONSTANT)
    Q_PROPERTY(QString add_circle_outline READ add_circle_outline CONSTANT)
    Q_PROPERTY(QString add_comment READ add_comment CONSTANT)
    Q_PROPERTY(QString add_ic_call READ add_ic_call CONSTANT)
    Q_PROPERTY(QString add_link READ add_link CONSTANT)
    Q_PROPERTY(QString add_location READ add_location CONSTANT)
    Q_PROPERTY(QString add_moderator READ add_moderator CONSTANT)
    Q_PROPERTY(QString add_photo_alternate READ add_photo_alternate CONSTANT)
    Q_PROPERTY(QString add_shopping_cart READ add_shopping_cart CONSTANT)
    Q_PROPERTY(QString add_to_home_screen READ add_to_home_screen CONSTANT)
    Q_PROPERTY(QString add_to_photos READ add_to_photos CONSTANT)
    Q_PROPERTY(QString add_to_queue READ add_to_queue CONSTANT)
    Q_PROPERTY(QString adjust READ adjust CONSTANT)
    Q_PROPERTY(QString airline_seat_flat READ airline_seat_flat CONSTANT)
    Q_PROPERTY(QString airline_seat_flat_angled READ airline_seat_flat_angled CONSTANT)
    Q_PROPERTY(QString airline_seat_individual_suite READ airline_seat_individual_suite CONSTANT)
    Q_PROPERTY(QString airline_seat_legroom_extra READ airline_seat_legroom_extra CONSTANT)
    Q_PROPERTY(QString airline_seat_legroom_normal READ airline_seat_legroom_normal CONSTANT)
    Q_PROPERTY(QString airline_seat_legroom_reduced READ airline_seat_legroom_reduced CONSTANT)
    Q_PROPERTY(QString airline_seat_recline_extra READ airline_seat_recline_extra CONSTANT)
    Q_PROPERTY(QString airline_seat_recline_normal READ airline_seat_recline_normal CONSTANT)
    Q_PROPERTY(QString airplanemode_active READ airplanemode_active CONSTANT)
    Q_PROPERTY(QString airplanemode_inactive READ airplanemode_inactive CONSTANT)
    Q_PROPERTY(QString airplanemode_off READ airplanemode_off CONSTANT)
    Q_PROPERTY(QString airplanemode_on READ airplanemode_on CONSTANT)
    Q_PROPERTY(QString airplay READ airplay CONSTANT)
    Q_PROPERTY(QString airport_shuttle READ airport_shuttle CONSTANT)
    Q_PROPERTY(QString alarm READ alarm CONSTANT)
    Q_PROPERTY(QString alarm_add READ alarm_add CONSTANT)
    Q_PROPERTY(QString alarm_off READ alarm_off CONSTANT)
    Q_PROPERTY(QString alarm_on READ alarm_on CONSTANT)
    Q_PROPERTY(QString album READ album CONSTANT)
    Q_PROPERTY(QString all_inbox READ all_inbox CONSTANT)
    Q_PROPERTY(QString all_inclusive READ all_inclusive CONSTANT)
    Q_PROPERTY(QString all_out READ all_out CONSTANT)
    Q_PROPERTY(QString alternate_email READ alternate_email CONSTANT)
    Q_PROPERTY(QString amp_stories READ amp_stories CONSTANT)
    Q_PROPERTY(QString android READ android CONSTANT)
    Q_PROPERTY(QString announcement READ announcement CONSTANT)
    Q_PROPERTY(QString apartment READ apartment CONSTANT)
    Q_PROPERTY(QString approval READ approval CONSTANT)
    Q_PROPERTY(QString apps READ apps CONSTANT)
    Q_PROPERTY(QString archive READ archive CONSTANT)
    Q_PROPERTY(QString arrow_back READ arrow_back CONSTANT)
    Q_PROPERTY(QString arrow_back_ios READ arrow_back_ios CONSTANT)
    Q_PROPERTY(QString arrow_downward READ arrow_downward CONSTANT)
    Q_PROPERTY(QString arrow_drop_down READ arrow_drop_down CONSTANT)
    Q_PROPERTY(QString arrow_drop_down_circle READ arrow_drop_down_circle CONSTANT)
    Q_PROPERTY(QString arrow_drop_up READ arrow_drop_up CONSTANT)
    Q_PROPERTY(QString arrow_forward READ arrow_forward CONSTANT)
    Q_PROPERTY(QString arrow_forward_ios READ arrow_forward_ios CONSTANT)
    Q_PROPERTY(QString arrow_left READ arrow_left CONSTANT)
    Q_PROPERTY(QString arrow_right READ arrow_right CONSTANT)
    Q_PROPERTY(QString arrow_right_alt READ arrow_right_alt CONSTANT)
    Q_PROPERTY(QString arrow_upward READ arrow_upward CONSTANT)
    Q_PROPERTY(QString art_track READ art_track CONSTANT)
    Q_PROPERTY(QString aspect_ratio READ aspect_ratio CONSTANT)
    Q_PROPERTY(QString assessment READ assessment CONSTANT)
    Q_PROPERTY(QString assignment READ assignment CONSTANT)
    Q_PROPERTY(QString assignment_ind READ assignment_ind CONSTANT)
    Q_PROPERTY(QString assignment_late READ assignment_late CONSTANT)
    Q_PROPERTY(QString assignment_return READ assignment_return CONSTANT)
    Q_PROPERTY(QString assignment_returned READ assignment_returned CONSTANT)
    Q_PROPERTY(QString assignment_turned_in READ assignment_turned_in CONSTANT)
    Q_PROPERTY(QString assistant READ assistant CONSTANT)
    Q_PROPERTY(QString assistant_direction READ assistant_direction CONSTANT)
    Q_PROPERTY(QString assistant_navigation READ assistant_navigation CONSTANT)
    Q_PROPERTY(QString assistant_photo READ assistant_photo CONSTANT)
    Q_PROPERTY(QString atm READ atm CONSTANT)
    Q_PROPERTY(QString attach_file READ attach_file CONSTANT)
    Q_PROPERTY(QString attach_money READ attach_money CONSTANT)
    Q_PROPERTY(QString attachment READ attachment CONSTANT)
    Q_PROPERTY(QString attractions READ attractions CONSTANT)
    Q_PROPERTY(QString audiotrack READ audiotrack CONSTANT)
    Q_PROPERTY(QString autorenew READ autorenew CONSTANT)
    Q_PROPERTY(QString av_timer READ av_timer CONSTANT)
    Q_PROPERTY(QString backspace READ backspace CONSTANT)
    Q_PROPERTY(QString backup READ backup CONSTANT)
    Q_PROPERTY(QString badge READ badge CONSTANT)
    Q_PROPERTY(QString bakery_dining READ bakery_dining CONSTANT)
    Q_PROPERTY(QString ballot READ ballot CONSTANT)
    Q_PROPERTY(QString bar_chart READ bar_chart CONSTANT)
    Q_PROPERTY(QString bathtub READ bathtub CONSTANT)
    Q_PROPERTY(QString battery_alert READ battery_alert CONSTANT)
    Q_PROPERTY(QString battery_charging_full READ battery_charging_full CONSTANT)
    Q_PROPERTY(QString battery_full READ battery_full CONSTANT)
    Q_PROPERTY(QString battery_std READ battery_std CONSTANT)
    Q_PROPERTY(QString battery_unknown READ battery_unknown CONSTANT)
    Q_PROPERTY(QString beach_access READ beach_access CONSTANT)
    Q_PROPERTY(QString beenhere READ beenhere CONSTANT)
    Q_PROPERTY(QString block READ block CONSTANT)
    Q_PROPERTY(QString bluetooth READ bluetooth CONSTANT)
    Q_PROPERTY(QString bluetooth_audio READ bluetooth_audio CONSTANT)
    Q_PROPERTY(QString bluetooth_connected READ bluetooth_connected CONSTANT)
    Q_PROPERTY(QString bluetooth_disabled READ bluetooth_disabled CONSTANT)
    Q_PROPERTY(QString bluetooth_searching READ bluetooth_searching CONSTANT)
    Q_PROPERTY(QString blur_circular READ blur_circular CONSTANT)
    Q_PROPERTY(QString blur_linear READ blur_linear CONSTANT)
    Q_PROPERTY(QString blur_off READ blur_off CONSTANT)
    Q_PROPERTY(QString blur_on READ blur_on CONSTANT)
    Q_PROPERTY(QString bolt READ bolt CONSTANT)
    Q_PROPERTY(QString book READ book CONSTANT)
    Q_PROPERTY(QString bookmark READ bookmark CONSTANT)
    Q_PROPERTY(QString bookmark_border READ bookmark_border CONSTANT)
    Q_PROPERTY(QString bookmark_outline READ bookmark_outline CONSTANT)
    Q_PROPERTY(QString bookmarks READ bookmarks CONSTANT)
    Q_PROPERTY(QString border_all READ border_all CONSTANT)
    Q_PROPERTY(QString border_bottom READ border_bottom CONSTANT)
    Q_PROPERTY(QString border_clear READ border_clear CONSTANT)
    Q_PROPERTY(QString border_color READ border_color CONSTANT)
    Q_PROPERTY(QString border_horizontal READ border_horizontal CONSTANT)
    Q_PROPERTY(QString border_inner READ border_inner CONSTANT)
    Q_PROPERTY(QString border_left READ border_left CONSTANT)
    Q_PROPERTY(QString border_outer READ border_outer CONSTANT)
    Q_PROPERTY(QString border_right READ border_right CONSTANT)
    Q_PROPERTY(QString border_style READ border_style CONSTANT)
    Q_PROPERTY(QString border_top READ border_top CONSTANT)
    Q_PROPERTY(QString border_vertical READ border_vertical CONSTANT)
    Q_PROPERTY(QString branding_watermark READ branding_watermark CONSTANT)
    Q_PROPERTY(QString breakfast_dining READ breakfast_dining CONSTANT)
    Q_PROPERTY(QString brightness_1 READ brightness_1 CONSTANT)
    Q_PROPERTY(QString brightness_2 READ brightness_2 CONSTANT)
    Q_PROPERTY(QString brightness_3 READ brightness_3 CONSTANT)
    Q_PROPERTY(QString brightness_4 READ brightness_4 CONSTANT)
    Q_PROPERTY(QString brightness_5 READ brightness_5 CONSTANT)
    Q_PROPERTY(QString brightness_6 READ brightness_6 CONSTANT)
    Q_PROPERTY(QString brightness_7 READ brightness_7 CONSTANT)
    Q_PROPERTY(QString brightness_auto READ brightness_auto CONSTANT)
    Q_PROPERTY(QString brightness_high READ brightness_high CONSTANT)
    Q_PROPERTY(QString brightness_low READ brightness_low CONSTANT)
    Q_PROPERTY(QString brightness_medium READ brightness_medium CONSTANT)
    Q_PROPERTY(QString broken_image READ broken_image CONSTANT)
    Q_PROPERTY(QString brunch_dining READ brunch_dining CONSTANT)
    Q_PROPERTY(QString brush READ brush CONSTANT)
    Q_PROPERTY(QString bubble_chart READ bubble_chart CONSTANT)
    Q_PROPERTY(QString bug_report READ bug_report CONSTANT)
    Q_PROPERTY(QString build READ build CONSTANT)
    Q_PROPERTY(QString burst_mode READ burst_mode CONSTANT)
    Q_PROPERTY(QString bus_alert READ bus_alert CONSTANT)
    Q_PROPERTY(QString business READ business CONSTANT)
    Q_PROPERTY(QString business_center READ business_center CONSTANT)
    Q_PROPERTY(QString cached READ cached CONSTANT)
    Q_PROPERTY(QString cake READ cake CONSTANT)
    Q_PROPERTY(QString calendar_today READ calendar_today CONSTANT)
    Q_PROPERTY(QString calendar_view_day READ calendar_view_day CONSTANT)
    Q_PROPERTY(QString call READ call CONSTANT)
    Q_PROPERTY(QString call_end READ call_end CONSTANT)
    Q_PROPERTY(QString call_made READ call_made CONSTANT)
    Q_PROPERTY(QString call_merge READ call_merge CONSTANT)
    Q_PROPERTY(QString call_missed READ call_missed CONSTANT)
    Q_PROPERTY(QString call_missed_outgoing READ call_missed_outgoing CONSTANT)
    Q_PROPERTY(QString call_received READ call_received CONSTANT)
    Q_PROPERTY(QString call_split READ call_split CONSTANT)
    Q_PROPERTY(QString call_to_action READ call_to_action CONSTANT)
    Q_PROPERTY(QString camera READ camera CONSTANT)
    Q_PROPERTY(QString camera_alt READ camera_alt CONSTANT)
    Q_PROPERTY(QString camera_enhance READ camera_enhance CONSTANT)
    Q_PROPERTY(QString camera_front READ camera_front CONSTANT)
    Q_PROPERTY(QString camera_rear READ camera_rear CONSTANT)
    Q_PROPERTY(QString camera_roll READ camera_roll CONSTANT)
    Q_PROPERTY(QString cancel READ cancel CONSTANT)
    Q_PROPERTY(QString cancel_presentation READ cancel_presentation CONSTANT)
    Q_PROPERTY(QString cancel_schedule_send READ cancel_schedule_send CONSTANT)
    Q_PROPERTY(QString car_rental READ car_rental CONSTANT)
    Q_PROPERTY(QString car_repair READ car_repair CONSTANT)
    Q_PROPERTY(QString card_giftcard READ card_giftcard CONSTANT)
    Q_PROPERTY(QString card_membership READ card_membership CONSTANT)
    Q_PROPERTY(QString card_travel READ card_travel CONSTANT)
    Q_PROPERTY(QString cases READ cases CONSTANT)
    Q_PROPERTY(QString casino READ casino CONSTANT)
    Q_PROPERTY(QString cast READ cast CONSTANT)
    Q_PROPERTY(QString cast_connected READ cast_connected CONSTANT)
    Q_PROPERTY(QString category READ category CONSTANT)
    Q_PROPERTY(QString celebration READ celebration CONSTANT)
    Q_PROPERTY(QString cell_wifi READ cell_wifi CONSTANT)
    Q_PROPERTY(QString center_focus_strong READ center_focus_strong CONSTANT)
    Q_PROPERTY(QString center_focus_weak READ center_focus_weak CONSTANT)
    Q_PROPERTY(QString change_history READ change_history CONSTANT)
    Q_PROPERTY(QString chat READ chat CONSTANT)
    Q_PROPERTY(QString chat_bubble READ chat_bubble CONSTANT)
    Q_PROPERTY(QString chat_bubble_outline READ chat_bubble_outline CONSTANT)
    Q_PROPERTY(QString check READ check CONSTANT)
    Q_PROPERTY(QString check_box READ check_box CONSTANT)
    Q_PROPERTY(QString check_box_outline_blank READ check_box_outline_blank CONSTANT)
    Q_PROPERTY(QString check_circle READ check_circle CONSTANT)
    Q_PROPERTY(QString check_circle_outline READ check_circle_outline CONSTANT)
    Q_PROPERTY(QString chevron_left READ chevron_left CONSTANT)
    Q_PROPERTY(QString chevron_right READ chevron_right CONSTANT)
    Q_PROPERTY(QString child_care READ child_care CONSTANT)
    Q_PROPERTY(QString child_friendly READ child_friendly CONSTANT)
    Q_PROPERTY(QString chrome_reader_mode READ chrome_reader_mode CONSTANT)
    Q_PROPERTY(QString circle_notifications READ circle_notifications CONSTANT)
    Q_PROPERTY(QString clear READ clear CONSTANT)
    Q_PROPERTY(QString clear_all READ clear_all CONSTANT)
    Q_PROPERTY(QString close READ close CONSTANT)
    Q_PROPERTY(QString closed_caption READ closed_caption CONSTANT)
    Q_PROPERTY(QString closed_caption_off READ closed_caption_off CONSTANT)
    Q_PROPERTY(QString cloud READ cloud CONSTANT)
    Q_PROPERTY(QString cloud_circle READ cloud_circle CONSTANT)
    Q_PROPERTY(QString cloud_done READ cloud_done CONSTANT)
    Q_PROPERTY(QString cloud_download READ cloud_download CONSTANT)
    Q_PROPERTY(QString cloud_off READ cloud_off CONSTANT)
    Q_PROPERTY(QString cloud_queue READ cloud_queue CONSTANT)
    Q_PROPERTY(QString cloud_upload READ cloud_upload CONSTANT)
    Q_PROPERTY(QString code READ code CONSTANT)
    Q_PROPERTY(QString collections READ collections CONSTANT)
    Q_PROPERTY(QString collections_bookmark READ collections_bookmark CONSTANT)
    Q_PROPERTY(QString color_lens READ color_lens CONSTANT)
    Q_PROPERTY(QString colorize READ colorize CONSTANT)
    Q_PROPERTY(QString comment READ comment CONSTANT)
    Q_PROPERTY(QString commute READ commute CONSTANT)
    Q_PROPERTY(QString compare READ compare CONSTANT)
    Q_PROPERTY(QString compare_arrows READ compare_arrows CONSTANT)
    Q_PROPERTY(QString compass_calibration READ compass_calibration CONSTANT)
    Q_PROPERTY(QString compress READ compress CONSTANT)
    Q_PROPERTY(QString computer READ computer CONSTANT)
    Q_PROPERTY(QString confirmation_num READ confirmation_num CONSTANT)
    Q_PROPERTY(QString confirmation_number READ confirmation_number CONSTANT)
    Q_PROPERTY(QString connected_tv READ connected_tv CONSTANT)
    Q_PROPERTY(QString contact_mail READ contact_mail CONSTANT)
    Q_PROPERTY(QString contact_phone READ contact_phone CONSTANT)
    Q_PROPERTY(QString contact_support READ contact_support CONSTANT)
    Q_PROPERTY(QString contactless READ contactless CONSTANT)
    Q_PROPERTY(QString contacts READ contacts CONSTANT)
    Q_PROPERTY(QString content_copy READ content_copy CONSTANT)
    Q_PROPERTY(QString content_cut READ content_cut CONSTANT)
    Q_PROPERTY(QString content_paste READ content_paste CONSTANT)
    Q_PROPERTY(QString control_camera READ control_camera CONSTANT)
    Q_PROPERTY(QString control_point READ control_point CONSTANT)
    Q_PROPERTY(QString control_point_duplicate READ control_point_duplicate CONSTANT)
    Q_PROPERTY(QString copyright READ copyright CONSTANT)
    Q_PROPERTY(QString create READ create CONSTANT)
    Q_PROPERTY(QString create_new_folder READ create_new_folder CONSTANT)
    Q_PROPERTY(QString credit_card READ credit_card CONSTANT)
    Q_PROPERTY(QString crop READ crop CONSTANT)
    Q_PROPERTY(QString crop_16_9 READ crop_16_9 CONSTANT)
    Q_PROPERTY(QString crop_3_2 READ crop_3_2 CONSTANT)
    Q_PROPERTY(QString crop_5_4 READ crop_5_4 CONSTANT)
    Q_PROPERTY(QString crop_7_5 READ crop_7_5 CONSTANT)
    Q_PROPERTY(QString crop_din READ crop_din CONSTANT)
    Q_PROPERTY(QString crop_free READ crop_free CONSTANT)
    Q_PROPERTY(QString crop_landscape READ crop_landscape CONSTANT)
    Q_PROPERTY(QString crop_original READ crop_original CONSTANT)
    Q_PROPERTY(QString crop_portrait READ crop_portrait CONSTANT)
    Q_PROPERTY(QString crop_rotate READ crop_rotate CONSTANT)
    Q_PROPERTY(QString crop_square READ crop_square CONSTANT)
    Q_PROPERTY(QString dangerous READ dangerous CONSTANT)
    Q_PROPERTY(QString dashboard READ dashboard CONSTANT)
    Q_PROPERTY(QString dashboard_customize READ dashboard_customize CONSTANT)
    Q_PROPERTY(QString data_usage READ data_usage CONSTANT)
    Q_PROPERTY(QString date_range READ date_range CONSTANT)
    Q_PROPERTY(QString deck READ deck CONSTANT)
    Q_PROPERTY(QString dehaze READ dehaze CONSTANT)
    Q_PROPERTY(QString delete_forever READ delete_forever CONSTANT)
    Q_PROPERTY(QString delete_outline READ delete_outline CONSTANT)
    Q_PROPERTY(QString delete_sweep READ delete_sweep CONSTANT)
    Q_PROPERTY(QString delivery_dining READ delivery_dining CONSTANT)
    Q_PROPERTY(QString departure_board READ departure_board CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QString desktop_access_disabled READ desktop_access_disabled CONSTANT)
    Q_PROPERTY(QString desktop_mac READ desktop_mac CONSTANT)
    Q_PROPERTY(QString desktop_windows READ desktop_windows CONSTANT)
    Q_PROPERTY(QString details READ details CONSTANT)
    Q_PROPERTY(QString developer_board READ developer_board CONSTANT)
    Q_PROPERTY(QString developer_mode READ developer_mode CONSTANT)
    Q_PROPERTY(QString device_hub READ device_hub CONSTANT)
    Q_PROPERTY(QString device_thermostat READ device_thermostat CONSTANT)
    Q_PROPERTY(QString device_unknown READ device_unknown CONSTANT)
    Q_PROPERTY(QString devices READ devices CONSTANT)
    Q_PROPERTY(QString devices_other READ devices_other CONSTANT)
    Q_PROPERTY(QString dialer_sip READ dialer_sip CONSTANT)
    Q_PROPERTY(QString dialpad READ dialpad CONSTANT)
    Q_PROPERTY(QString dinner_dining READ dinner_dining CONSTANT)
    Q_PROPERTY(QString directions READ directions CONSTANT)
    Q_PROPERTY(QString directions_bike READ directions_bike CONSTANT)
    Q_PROPERTY(QString directions_boat READ directions_boat CONSTANT)
    Q_PROPERTY(QString directions_bus READ directions_bus CONSTANT)
    Q_PROPERTY(QString directions_car READ directions_car CONSTANT)
    Q_PROPERTY(QString directions_ferry READ directions_ferry CONSTANT)
    Q_PROPERTY(QString directions_railway READ directions_railway CONSTANT)
    Q_PROPERTY(QString directions_run READ directions_run CONSTANT)
    Q_PROPERTY(QString directions_subway READ directions_subway CONSTANT)
    Q_PROPERTY(QString directions_train READ directions_train CONSTANT)
    Q_PROPERTY(QString directions_transit READ directions_transit CONSTANT)
    Q_PROPERTY(QString directions_walk READ directions_walk CONSTANT)
    Q_PROPERTY(QString disc_full READ disc_full CONSTANT)
    Q_PROPERTY(QString dnd_forwardslash READ dnd_forwardslash CONSTANT)
    Q_PROPERTY(QString dns READ dns CONSTANT)
    Q_PROPERTY(QString do_not_disturb READ do_not_disturb CONSTANT)
    Q_PROPERTY(QString do_not_disturb_alt READ do_not_disturb_alt CONSTANT)
    Q_PROPERTY(QString do_not_disturb_off READ do_not_disturb_off CONSTANT)
    Q_PROPERTY(QString do_not_disturb_on READ do_not_disturb_on CONSTANT)
    Q_PROPERTY(QString dock READ dock CONSTANT)
    Q_PROPERTY(QString domain READ domain CONSTANT)
    Q_PROPERTY(QString domain_disabled READ domain_disabled CONSTANT)
    Q_PROPERTY(QString done READ done CONSTANT)
    Q_PROPERTY(QString done_all READ done_all CONSTANT)
    Q_PROPERTY(QString done_outline READ done_outline CONSTANT)
    Q_PROPERTY(QString donut_large READ donut_large CONSTANT)
    Q_PROPERTY(QString donut_small READ donut_small CONSTANT)
    Q_PROPERTY(QString double_arrow READ double_arrow CONSTANT)
    Q_PROPERTY(QString drafts READ drafts CONSTANT)
    Q_PROPERTY(QString drag_handle READ drag_handle CONSTANT)
    Q_PROPERTY(QString drag_indicator READ drag_indicator CONSTANT)
    Q_PROPERTY(QString drive_eta READ drive_eta CONSTANT)
    Q_PROPERTY(QString drive_file_move_outline READ drive_file_move_outline CONSTANT)
    Q_PROPERTY(QString drive_file_rename_outline READ drive_file_rename_outline CONSTANT)
    Q_PROPERTY(QString drive_folder_upload READ drive_folder_upload CONSTANT)
    Q_PROPERTY(QString dry_cleaning READ dry_cleaning CONSTANT)
    Q_PROPERTY(QString duo READ duo CONSTANT)
    Q_PROPERTY(QString dvr READ dvr CONSTANT)
    Q_PROPERTY(QString dynamic_feed READ dynamic_feed CONSTANT)
    Q_PROPERTY(QString eco READ eco CONSTANT)
    Q_PROPERTY(QString edit READ edit CONSTANT)
    Q_PROPERTY(QString edit_attributes READ edit_attributes CONSTANT)
    Q_PROPERTY(QString edit_location READ edit_location CONSTANT)
    Q_PROPERTY(QString edit_off READ edit_off CONSTANT)
    Q_PROPERTY(QString eject READ eject CONSTANT)
    Q_PROPERTY(QString email READ email CONSTANT)
    Q_PROPERTY(QString emoji_emotions READ emoji_emotions CONSTANT)
    Q_PROPERTY(QString emoji_events READ emoji_events CONSTANT)
    Q_PROPERTY(QString emoji_flags READ emoji_flags CONSTANT)
    Q_PROPERTY(QString emoji_food_beverage READ emoji_food_beverage CONSTANT)
    Q_PROPERTY(QString emoji_nature READ emoji_nature CONSTANT)
    Q_PROPERTY(QString emoji_objects READ emoji_objects CONSTANT)
    Q_PROPERTY(QString emoji_people READ emoji_people CONSTANT)
    Q_PROPERTY(QString emoji_symbols READ emoji_symbols CONSTANT)
    Q_PROPERTY(QString emoji_transportation READ emoji_transportation CONSTANT)
    Q_PROPERTY(QString enhance_photo_translate READ enhance_photo_translate CONSTANT)
    Q_PROPERTY(QString enhanced_encryption READ enhanced_encryption CONSTANT)
    Q_PROPERTY(QString equalizer READ equalizer CONSTANT)
    Q_PROPERTY(QString error READ error CONSTANT)
    Q_PROPERTY(QString error_outline READ error_outline CONSTANT)
    Q_PROPERTY(QString euro READ euro CONSTANT)
    Q_PROPERTY(QString euro_symbol READ euro_symbol CONSTANT)
    Q_PROPERTY(QString ev_station READ ev_station CONSTANT)
    Q_PROPERTY(QString event READ event CONSTANT)
    Q_PROPERTY(QString event_available READ event_available CONSTANT)
    Q_PROPERTY(QString event_busy READ event_busy CONSTANT)
    Q_PROPERTY(QString event_note READ event_note CONSTANT)
    Q_PROPERTY(QString event_seat READ event_seat CONSTANT)
    Q_PROPERTY(QString exit_to_app READ exit_to_app CONSTANT)
    Q_PROPERTY(QString expand READ expand CONSTANT)
    Q_PROPERTY(QString expand_less READ expand_less CONSTANT)
    Q_PROPERTY(QString expand_more READ expand_more CONSTANT)
    Q_PROPERTY(QString explore READ explore CONSTANT)
    Q_PROPERTY(QString explore_off READ explore_off CONSTANT)
    Q_PROPERTY(QString exposure READ exposure CONSTANT)
    Q_PROPERTY(QString exposure_minus_1 READ exposure_minus_1 CONSTANT)
    Q_PROPERTY(QString exposure_minus_2 READ exposure_minus_2 CONSTANT)
    Q_PROPERTY(QString exposure_neg_1 READ exposure_neg_1 CONSTANT)
    Q_PROPERTY(QString exposure_neg_2 READ exposure_neg_2 CONSTANT)
    Q_PROPERTY(QString exposure_plus_1 READ exposure_plus_1 CONSTANT)
    Q_PROPERTY(QString exposure_plus_2 READ exposure_plus_2 CONSTANT)
    Q_PROPERTY(QString exposure_zero READ exposure_zero CONSTANT)
    Q_PROPERTY(QString extension READ extension CONSTANT)
    Q_PROPERTY(QString face READ face CONSTANT)
    Q_PROPERTY(QString fast_forward READ fast_forward CONSTANT)
    Q_PROPERTY(QString fast_rewind READ fast_rewind CONSTANT)
    Q_PROPERTY(QString fastfood READ fastfood CONSTANT)
    Q_PROPERTY(QString favorite READ favorite CONSTANT)
    Q_PROPERTY(QString favorite_border READ favorite_border CONSTANT)
    Q_PROPERTY(QString favorite_outline READ favorite_outline CONSTANT)
    Q_PROPERTY(QString featured_play_list READ featured_play_list CONSTANT)
    Q_PROPERTY(QString featured_video READ featured_video CONSTANT)
    Q_PROPERTY(QString feedback READ feedback CONSTANT)
    Q_PROPERTY(QString festival READ festival CONSTANT)
    Q_PROPERTY(QString fiber_dvr READ fiber_dvr CONSTANT)
    Q_PROPERTY(QString fiber_manual_record READ fiber_manual_record CONSTANT)
    Q_PROPERTY(QString fiber_new READ fiber_new CONSTANT)
    Q_PROPERTY(QString fiber_pin READ fiber_pin CONSTANT)
    Q_PROPERTY(QString fiber_smart_record READ fiber_smart_record CONSTANT)
    Q_PROPERTY(QString file_copy READ file_copy CONSTANT)
    Q_PROPERTY(QString file_download READ file_download CONSTANT)
    Q_PROPERTY(QString file_download_done READ file_download_done CONSTANT)
    Q_PROPERTY(QString file_present READ file_present CONSTANT)
    Q_PROPERTY(QString file_upload READ file_upload CONSTANT)
    Q_PROPERTY(QString filter READ filter CONSTANT)
    Q_PROPERTY(QString filter_1 READ filter_1 CONSTANT)
    Q_PROPERTY(QString filter_2 READ filter_2 CONSTANT)
    Q_PROPERTY(QString filter_3 READ filter_3 CONSTANT)
    Q_PROPERTY(QString filter_4 READ filter_4 CONSTANT)
    Q_PROPERTY(QString filter_5 READ filter_5 CONSTANT)
    Q_PROPERTY(QString filter_6 READ filter_6 CONSTANT)
    Q_PROPERTY(QString filter_7 READ filter_7 CONSTANT)
    Q_PROPERTY(QString filter_8 READ filter_8 CONSTANT)
    Q_PROPERTY(QString filter_9 READ filter_9 CONSTANT)
    Q_PROPERTY(QString filter_9_plus READ filter_9_plus CONSTANT)
    Q_PROPERTY(QString filter_b_and_w READ filter_b_and_w CONSTANT)
    Q_PROPERTY(QString filter_center_focus READ filter_center_focus CONSTANT)
    Q_PROPERTY(QString filter_drama READ filter_drama CONSTANT)
    Q_PROPERTY(QString filter_frames READ filter_frames CONSTANT)
    Q_PROPERTY(QString filter_hdr READ filter_hdr CONSTANT)
    Q_PROPERTY(QString filter_list READ filter_list CONSTANT)
    Q_PROPERTY(QString filter_list_alt READ filter_list_alt CONSTANT)
    Q_PROPERTY(QString filter_none READ filter_none CONSTANT)
    Q_PROPERTY(QString filter_tilt_shift READ filter_tilt_shift CONSTANT)
    Q_PROPERTY(QString filter_vintage READ filter_vintage CONSTANT)
    Q_PROPERTY(QString find_in_page READ find_in_page CONSTANT)
    Q_PROPERTY(QString find_replace READ find_replace CONSTANT)
    Q_PROPERTY(QString fingerprint READ fingerprint CONSTANT)
    Q_PROPERTY(QString fireplace READ fireplace CONSTANT)
    Q_PROPERTY(QString first_page READ first_page CONSTANT)
    Q_PROPERTY(QString fit_screen READ fit_screen CONSTANT)
    Q_PROPERTY(QString fitness_center READ fitness_center CONSTANT)
    Q_PROPERTY(QString flag READ flag CONSTANT)
    Q_PROPERTY(QString flare READ flare CONSTANT)
    Q_PROPERTY(QString flash_auto READ flash_auto CONSTANT)
    Q_PROPERTY(QString flash_off READ flash_off CONSTANT)
    Q_PROPERTY(QString flash_on READ flash_on CONSTANT)
    Q_PROPERTY(QString flight READ flight CONSTANT)
    Q_PROPERTY(QString flight_land READ flight_land CONSTANT)
    Q_PROPERTY(QString flight_takeoff READ flight_takeoff CONSTANT)
    Q_PROPERTY(QString flip READ flip CONSTANT)
    Q_PROPERTY(QString flip_camera_android READ flip_camera_android CONSTANT)
    Q_PROPERTY(QString flip_camera_ios READ flip_camera_ios CONSTANT)
    Q_PROPERTY(QString flip_to_back READ flip_to_back CONSTANT)
    Q_PROPERTY(QString flip_to_front READ flip_to_front CONSTANT)
    Q_PROPERTY(QString folder READ folder CONSTANT)
    Q_PROPERTY(QString folder_open READ folder_open CONSTANT)
    Q_PROPERTY(QString folder_shared READ folder_shared CONSTANT)
    Q_PROPERTY(QString folder_special READ folder_special CONSTANT)
    Q_PROPERTY(QString font_download READ font_download CONSTANT)
    Q_PROPERTY(QString format_align_center READ format_align_center CONSTANT)
    Q_PROPERTY(QString format_align_justify READ format_align_justify CONSTANT)
    Q_PROPERTY(QString format_align_left READ format_align_left CONSTANT)
    Q_PROPERTY(QString format_align_right READ format_align_right CONSTANT)
    Q_PROPERTY(QString format_bold READ format_bold CONSTANT)
    Q_PROPERTY(QString format_clear READ format_clear CONSTANT)
    Q_PROPERTY(QString format_color_fill READ format_color_fill CONSTANT)
    Q_PROPERTY(QString format_color_reset READ format_color_reset CONSTANT)
    Q_PROPERTY(QString format_color_text READ format_color_text CONSTANT)
    Q_PROPERTY(QString format_indent_decrease READ format_indent_decrease CONSTANT)
    Q_PROPERTY(QString format_indent_increase READ format_indent_increase CONSTANT)
    Q_PROPERTY(QString format_italic READ format_italic CONSTANT)
    Q_PROPERTY(QString format_line_spacing READ format_line_spacing CONSTANT)
    Q_PROPERTY(QString format_list_bulleted READ format_list_bulleted CONSTANT)
    Q_PROPERTY(QString format_list_numbered READ format_list_numbered CONSTANT)
    Q_PROPERTY(QString format_list_numbered_rtl READ format_list_numbered_rtl CONSTANT)
    Q_PROPERTY(QString format_paint READ format_paint CONSTANT)
    Q_PROPERTY(QString format_quote READ format_quote CONSTANT)
    Q_PROPERTY(QString format_shapes READ format_shapes CONSTANT)
    Q_PROPERTY(QString format_size READ format_size CONSTANT)
    Q_PROPERTY(QString format_strikethrough READ format_strikethrough CONSTANT)
    Q_PROPERTY(QString format_textdirection_l_to_r READ format_textdirection_l_to_r CONSTANT)
    Q_PROPERTY(QString format_textdirection_r_to_l READ format_textdirection_r_to_l CONSTANT)
    Q_PROPERTY(QString format_underline READ format_underline CONSTANT)
    Q_PROPERTY(QString format_underlined READ format_underlined CONSTANT)
    Q_PROPERTY(QString forum READ forum CONSTANT)
    Q_PROPERTY(QString forward READ forward CONSTANT)
    Q_PROPERTY(QString forward_10 READ forward_10 CONSTANT)
    Q_PROPERTY(QString forward_30 READ forward_30 CONSTANT)
    Q_PROPERTY(QString forward_5 READ forward_5 CONSTANT)
    Q_PROPERTY(QString free_breakfast READ free_breakfast CONSTANT)
    Q_PROPERTY(QString fullscreen READ fullscreen CONSTANT)
    Q_PROPERTY(QString fullscreen_exit READ fullscreen_exit CONSTANT)
    Q_PROPERTY(QString functions READ functions CONSTANT)
    Q_PROPERTY(QString g_translate READ g_translate CONSTANT)
    Q_PROPERTY(QString gamepad READ gamepad CONSTANT)
    Q_PROPERTY(QString games READ games CONSTANT)
    Q_PROPERTY(QString gavel READ gavel CONSTANT)
    Q_PROPERTY(QString gesture READ gesture CONSTANT)
    Q_PROPERTY(QString get_app READ get_app CONSTANT)
    Q_PROPERTY(QString gif READ gif CONSTANT)
    Q_PROPERTY(QString goat READ goat CONSTANT)
    Q_PROPERTY(QString golf_course READ golf_course CONSTANT)
    Q_PROPERTY(QString gps_fixed READ gps_fixed CONSTANT)
    Q_PROPERTY(QString gps_not_fixed READ gps_not_fixed CONSTANT)
    Q_PROPERTY(QString gps_off READ gps_off CONSTANT)
    Q_PROPERTY(QString grade READ grade CONSTANT)
    Q_PROPERTY(QString gradient READ gradient CONSTANT)
    Q_PROPERTY(QString grain READ grain CONSTANT)
    Q_PROPERTY(QString graphic_eq READ graphic_eq CONSTANT)
    Q_PROPERTY(QString grid_off READ grid_off CONSTANT)
    Q_PROPERTY(QString grid_on READ grid_on CONSTANT)
    Q_PROPERTY(QString grid_view READ grid_view CONSTANT)
    Q_PROPERTY(QString group READ group CONSTANT)
    Q_PROPERTY(QString group_add READ group_add CONSTANT)
    Q_PROPERTY(QString group_work READ group_work CONSTANT)
    Q_PROPERTY(QString hail READ hail CONSTANT)
    Q_PROPERTY(QString hardware READ hardware CONSTANT)
    Q_PROPERTY(QString hd READ hd CONSTANT)
    Q_PROPERTY(QString hdr_off READ hdr_off CONSTANT)
    Q_PROPERTY(QString hdr_on READ hdr_on CONSTANT)
    Q_PROPERTY(QString hdr_strong READ hdr_strong CONSTANT)
    Q_PROPERTY(QString hdr_weak READ hdr_weak CONSTANT)
    Q_PROPERTY(QString headset READ headset CONSTANT)
    Q_PROPERTY(QString headset_mic READ headset_mic CONSTANT)
    Q_PROPERTY(QString headset_off READ headset_off CONSTANT)
    Q_PROPERTY(QString healing READ healing CONSTANT)
    Q_PROPERTY(QString hearing READ hearing CONSTANT)
    Q_PROPERTY(QString height READ height CONSTANT)
    Q_PROPERTY(QString help READ help CONSTANT)
    Q_PROPERTY(QString help_outline READ help_outline CONSTANT)
    Q_PROPERTY(QString high_quality READ high_quality CONSTANT)
    Q_PROPERTY(QString highlight READ highlight CONSTANT)
    Q_PROPERTY(QString highlight_off READ highlight_off CONSTANT)
    Q_PROPERTY(QString highlight_remove READ highlight_remove CONSTANT)
    Q_PROPERTY(QString history READ history CONSTANT)
    Q_PROPERTY(QString home READ home CONSTANT)
    Q_PROPERTY(QString home_filled READ home_filled CONSTANT)
    Q_PROPERTY(QString home_work READ home_work CONSTANT)
    Q_PROPERTY(QString horizontal_split READ horizontal_split CONSTANT)
    Q_PROPERTY(QString hot_tub READ hot_tub CONSTANT)
    Q_PROPERTY(QString hotel READ hotel CONSTANT)
    Q_PROPERTY(QString hourglass_empty READ hourglass_empty CONSTANT)
    Q_PROPERTY(QString hourglass_full READ hourglass_full CONSTANT)
    Q_PROPERTY(QString house READ house CONSTANT)
    Q_PROPERTY(QString how_to_reg READ how_to_reg CONSTANT)
    Q_PROPERTY(QString how_to_vote READ how_to_vote CONSTANT)
    Q_PROPERTY(QString http READ http CONSTANT)
    Q_PROPERTY(QString https READ https CONSTANT)
    Q_PROPERTY(QString icecream READ icecream CONSTANT)
    Q_PROPERTY(QString image READ image CONSTANT)
    Q_PROPERTY(QString image_aspect_ratio READ image_aspect_ratio CONSTANT)
    Q_PROPERTY(QString image_search READ image_search CONSTANT)
    Q_PROPERTY(QString imagesearch_roller READ imagesearch_roller CONSTANT)
    Q_PROPERTY(QString import_contacts READ import_contacts CONSTANT)
    Q_PROPERTY(QString import_export READ import_export CONSTANT)
    Q_PROPERTY(QString important_devices READ important_devices CONSTANT)
    Q_PROPERTY(QString inbox READ inbox CONSTANT)
    Q_PROPERTY(QString indeterminate_check_box READ indeterminate_check_box CONSTANT)
    Q_PROPERTY(QString info READ info CONSTANT)
    Q_PROPERTY(QString info_outline READ info_outline CONSTANT)
    Q_PROPERTY(QString input READ input CONSTANT)
    Q_PROPERTY(QString insert_chart READ insert_chart CONSTANT)
    Q_PROPERTY(QString insert_chart_outlined READ insert_chart_outlined CONSTANT)
    Q_PROPERTY(QString insert_comment READ insert_comment CONSTANT)
    Q_PROPERTY(QString insert_drive_file READ insert_drive_file CONSTANT)
    Q_PROPERTY(QString insert_emoticon READ insert_emoticon CONSTANT)
    Q_PROPERTY(QString insert_invitation READ insert_invitation CONSTANT)
    Q_PROPERTY(QString insert_link READ insert_link CONSTANT)
    Q_PROPERTY(QString insert_photo READ insert_photo CONSTANT)
    Q_PROPERTY(QString inventory READ inventory CONSTANT)
    Q_PROPERTY(QString invert_colors READ invert_colors CONSTANT)
    Q_PROPERTY(QString invert_colors_off READ invert_colors_off CONSTANT)
    Q_PROPERTY(QString invert_colors_on READ invert_colors_on CONSTANT)
    Q_PROPERTY(QString iso READ iso CONSTANT)
    Q_PROPERTY(QString keyboard READ keyboard CONSTANT)
    Q_PROPERTY(QString keyboard_arrow_down READ keyboard_arrow_down CONSTANT)
    Q_PROPERTY(QString keyboard_arrow_left READ keyboard_arrow_left CONSTANT)
    Q_PROPERTY(QString keyboard_arrow_right READ keyboard_arrow_right CONSTANT)
    Q_PROPERTY(QString keyboard_arrow_up READ keyboard_arrow_up CONSTANT)
    Q_PROPERTY(QString keyboard_backspace READ keyboard_backspace CONSTANT)
    Q_PROPERTY(QString keyboard_capslock READ keyboard_capslock CONSTANT)
    Q_PROPERTY(QString keyboard_control READ keyboard_control CONSTANT)
    Q_PROPERTY(QString keyboard_hide READ keyboard_hide CONSTANT)
    Q_PROPERTY(QString keyboard_return READ keyboard_return CONSTANT)
    Q_PROPERTY(QString keyboard_tab READ keyboard_tab CONSTANT)
    Q_PROPERTY(QString keyboard_voice READ keyboard_voice CONSTANT)
    Q_PROPERTY(QString king_bed READ king_bed CONSTANT)
    Q_PROPERTY(QString kitchen READ kitchen CONSTANT)
    Q_PROPERTY(QString label READ label CONSTANT)
    Q_PROPERTY(QString label_important READ label_important CONSTANT)
    Q_PROPERTY(QString label_important_outline READ label_important_outline CONSTANT)
    Q_PROPERTY(QString label_off READ label_off CONSTANT)
    Q_PROPERTY(QString label_outline READ label_outline CONSTANT)
    Q_PROPERTY(QString landscape READ landscape CONSTANT)
    Q_PROPERTY(QString language READ language CONSTANT)
    Q_PROPERTY(QString laptop READ laptop CONSTANT)
    Q_PROPERTY(QString laptop_chromebook READ laptop_chromebook CONSTANT)
    Q_PROPERTY(QString laptop_mac READ laptop_mac CONSTANT)
    Q_PROPERTY(QString laptop_windows READ laptop_windows CONSTANT)
    Q_PROPERTY(QString last_page READ last_page CONSTANT)
    Q_PROPERTY(QString launch READ launch CONSTANT)
    Q_PROPERTY(QString layers READ layers CONSTANT)
    Q_PROPERTY(QString layers_clear READ layers_clear CONSTANT)
    Q_PROPERTY(QString leak_add READ leak_add CONSTANT)
    Q_PROPERTY(QString leak_remove READ leak_remove CONSTANT)
    Q_PROPERTY(QString lens READ lens CONSTANT)
    Q_PROPERTY(QString library_add READ library_add CONSTANT)
    Q_PROPERTY(QString library_add_check READ library_add_check CONSTANT)
    Q_PROPERTY(QString library_books READ library_books CONSTANT)
    Q_PROPERTY(QString library_music READ library_music CONSTANT)
    Q_PROPERTY(QString lightbulb READ lightbulb CONSTANT)
    Q_PROPERTY(QString lightbulb_outline READ lightbulb_outline CONSTANT)
    Q_PROPERTY(QString line_style READ line_style CONSTANT)
    Q_PROPERTY(QString line_weight READ line_weight CONSTANT)
    Q_PROPERTY(QString linear_scale READ linear_scale CONSTANT)
    Q_PROPERTY(QString link READ link CONSTANT)
    Q_PROPERTY(QString link_off READ link_off CONSTANT)
    Q_PROPERTY(QString linked_camera READ linked_camera CONSTANT)
    Q_PROPERTY(QString liquor READ liquor CONSTANT)
    Q_PROPERTY(QString list READ list CONSTANT)
    Q_PROPERTY(QString list_alt READ list_alt CONSTANT)
    Q_PROPERTY(QString live_help READ live_help CONSTANT)
    Q_PROPERTY(QString live_tv READ live_tv CONSTANT)
    Q_PROPERTY(QString local_activity READ local_activity CONSTANT)
    Q_PROPERTY(QString local_airport READ local_airport CONSTANT)
    Q_PROPERTY(QString local_atm READ local_atm CONSTANT)
    Q_PROPERTY(QString local_attraction READ local_attraction CONSTANT)
    Q_PROPERTY(QString local_bar READ local_bar CONSTANT)
    Q_PROPERTY(QString local_cafe READ local_cafe CONSTANT)
    Q_PROPERTY(QString local_car_wash READ local_car_wash CONSTANT)
    Q_PROPERTY(QString local_convenience_store READ local_convenience_store CONSTANT)
    Q_PROPERTY(QString local_dining READ local_dining CONSTANT)
    Q_PROPERTY(QString local_drink READ local_drink CONSTANT)
    Q_PROPERTY(QString local_florist READ local_florist CONSTANT)
    Q_PROPERTY(QString local_gas_station READ local_gas_station CONSTANT)
    Q_PROPERTY(QString local_grocery_store READ local_grocery_store CONSTANT)
    Q_PROPERTY(QString local_hospital READ local_hospital CONSTANT)
    Q_PROPERTY(QString local_hotel READ local_hotel CONSTANT)
    Q_PROPERTY(QString local_laundry_service READ local_laundry_service CONSTANT)
    Q_PROPERTY(QString local_library READ local_library CONSTANT)
    Q_PROPERTY(QString local_mall READ local_mall CONSTANT)
    Q_PROPERTY(QString local_movies READ local_movies CONSTANT)
    Q_PROPERTY(QString local_offer READ local_offer CONSTANT)
    Q_PROPERTY(QString local_parking READ local_parking CONSTANT)
    Q_PROPERTY(QString local_pharmacy READ local_pharmacy CONSTANT)
    Q_PROPERTY(QString local_phone READ local_phone CONSTANT)
    Q_PROPERTY(QString local_pizza READ local_pizza CONSTANT)
    Q_PROPERTY(QString local_play READ local_play CONSTANT)
    Q_PROPERTY(QString local_post_office READ local_post_office CONSTANT)
    Q_PROPERTY(QString local_print_shop READ local_print_shop CONSTANT)
    Q_PROPERTY(QString local_printshop READ local_printshop CONSTANT)
    Q_PROPERTY(QString local_restaurant READ local_restaurant CONSTANT)
    Q_PROPERTY(QString local_see READ local_see CONSTANT)
    Q_PROPERTY(QString local_shipping READ local_shipping CONSTANT)
    Q_PROPERTY(QString local_taxi READ local_taxi CONSTANT)
    Q_PROPERTY(QString location_city READ location_city CONSTANT)
    Q_PROPERTY(QString location_disabled READ location_disabled CONSTANT)
    Q_PROPERTY(QString location_history READ location_history CONSTANT)
    Q_PROPERTY(QString location_off READ location_off CONSTANT)
    Q_PROPERTY(QString location_on READ location_on CONSTANT)
    Q_PROPERTY(QString location_searching READ location_searching CONSTANT)
    Q_PROPERTY(QString lock READ lock CONSTANT)
    Q_PROPERTY(QString lock_open READ lock_open CONSTANT)
    Q_PROPERTY(QString lock_outline READ lock_outline CONSTANT)
    Q_PROPERTY(QString logout READ logout CONSTANT)
    Q_PROPERTY(QString looks READ looks CONSTANT)
    Q_PROPERTY(QString looks_3 READ looks_3 CONSTANT)
    Q_PROPERTY(QString looks_4 READ looks_4 CONSTANT)
    Q_PROPERTY(QString looks_5 READ looks_5 CONSTANT)
    Q_PROPERTY(QString looks_6 READ looks_6 CONSTANT)
    Q_PROPERTY(QString looks_one READ looks_one CONSTANT)
    Q_PROPERTY(QString looks_two READ looks_two CONSTANT)
    Q_PROPERTY(QString loop READ loop CONSTANT)
    Q_PROPERTY(QString loupe READ loupe CONSTANT)
    Q_PROPERTY(QString low_priority READ low_priority CONSTANT)
    Q_PROPERTY(QString loyalty READ loyalty CONSTANT)
    Q_PROPERTY(QString lunch_dining READ lunch_dining CONSTANT)
    Q_PROPERTY(QString mail READ mail CONSTANT)
    Q_PROPERTY(QString mail_outline READ mail_outline CONSTANT)
    Q_PROPERTY(QString map READ map CONSTANT)
    Q_PROPERTY(QString margin READ margin CONSTANT)
    Q_PROPERTY(QString mark_as_unread READ mark_as_unread CONSTANT)
    Q_PROPERTY(QString markunread READ markunread CONSTANT)
    Q_PROPERTY(QString markunread_mailbox READ markunread_mailbox CONSTANT)
    Q_PROPERTY(QString maximize READ maximize CONSTANT)
    Q_PROPERTY(QString meeting_room READ meeting_room CONSTANT)
    Q_PROPERTY(QString memory READ memory CONSTANT)
    Q_PROPERTY(QString menu READ menu CONSTANT)
    Q_PROPERTY(QString menu_book READ menu_book CONSTANT)
    Q_PROPERTY(QString menu_open READ menu_open CONSTANT)
    Q_PROPERTY(QString merge_type READ merge_type CONSTANT)
    Q_PROPERTY(QString message READ message CONSTANT)
    Q_PROPERTY(QString messenger READ messenger CONSTANT)
    Q_PROPERTY(QString messenger_outline READ messenger_outline CONSTANT)
    Q_PROPERTY(QString mic READ mic CONSTANT)
    Q_PROPERTY(QString mic_none READ mic_none CONSTANT)
    Q_PROPERTY(QString mic_off READ mic_off CONSTANT)
    Q_PROPERTY(QString minimize READ minimize CONSTANT)
    Q_PROPERTY(QString missed_video_call READ missed_video_call CONSTANT)
    Q_PROPERTY(QString mms READ mms CONSTANT)
    Q_PROPERTY(QString mobile_friendly READ mobile_friendly CONSTANT)
    Q_PROPERTY(QString mobile_off READ mobile_off CONSTANT)
    Q_PROPERTY(QString mobile_screen_share READ mobile_screen_share CONSTANT)
    Q_PROPERTY(QString mode_comment READ mode_comment CONSTANT)
    Q_PROPERTY(QString mode_edit READ mode_edit CONSTANT)
    Q_PROPERTY(QString monetization_on READ monetization_on CONSTANT)
    Q_PROPERTY(QString money READ money CONSTANT)
    Q_PROPERTY(QString money_off READ money_off CONSTANT)
    Q_PROPERTY(QString monochrome_photos READ monochrome_photos CONSTANT)
    Q_PROPERTY(QString mood READ mood CONSTANT)
    Q_PROPERTY(QString mood_bad READ mood_bad CONSTANT)
    Q_PROPERTY(QString more READ more CONSTANT)
    Q_PROPERTY(QString more_horiz READ more_horiz CONSTANT)
    Q_PROPERTY(QString more_vert READ more_vert CONSTANT)
    Q_PROPERTY(QString motorcycle READ motorcycle CONSTANT)
    Q_PROPERTY(QString mouse READ mouse CONSTANT)
    Q_PROPERTY(QString move_to_inbox READ move_to_inbox CONSTANT)
    Q_PROPERTY(QString movie READ movie CONSTANT)
    Q_PROPERTY(QString movie_creation READ movie_creation CONSTANT)
    Q_PROPERTY(QString movie_filter READ movie_filter CONSTANT)
    Q_PROPERTY(QString mp READ mp CONSTANT)
    Q_PROPERTY(QString multiline_chart READ multiline_chart CONSTANT)
    Q_PROPERTY(QString multitrack_audio READ multitrack_audio CONSTANT)
    Q_PROPERTY(QString museum READ museum CONSTANT)
    Q_PROPERTY(QString music_note READ music_note CONSTANT)
    Q_PROPERTY(QString music_off READ music_off CONSTANT)
    Q_PROPERTY(QString music_video READ music_video CONSTANT)
    Q_PROPERTY(QString my_library_add READ my_library_add CONSTANT)
    Q_PROPERTY(QString my_library_books READ my_library_books CONSTANT)
    Q_PROPERTY(QString my_library_music READ my_library_music CONSTANT)
    Q_PROPERTY(QString my_location READ my_location CONSTANT)
    Q_PROPERTY(QString nature READ nature CONSTANT)
    Q_PROPERTY(QString nature_people READ nature_people CONSTANT)
    Q_PROPERTY(QString navigate_before READ navigate_before CONSTANT)
    Q_PROPERTY(QString navigate_next READ navigate_next CONSTANT)
    Q_PROPERTY(QString navigation READ navigation CONSTANT)
    Q_PROPERTY(QString near_me READ near_me CONSTANT)
    Q_PROPERTY(QString network_cell READ network_cell CONSTANT)
    Q_PROPERTY(QString network_check READ network_check CONSTANT)
    Q_PROPERTY(QString network_locked READ network_locked CONSTANT)
    Q_PROPERTY(QString network_wifi READ network_wifi CONSTANT)
    Q_PROPERTY(QString new_releases READ new_releases CONSTANT)
    Q_PROPERTY(QString next_week READ next_week CONSTANT)
    Q_PROPERTY(QString nfc READ nfc CONSTANT)
    Q_PROPERTY(QString nightlife READ nightlife CONSTANT)
    Q_PROPERTY(QString nights_stay READ nights_stay CONSTANT)
    Q_PROPERTY(QString no_encryption READ no_encryption CONSTANT)
    Q_PROPERTY(QString no_meeting_room READ no_meeting_room CONSTANT)
    Q_PROPERTY(QString no_sim READ no_sim CONSTANT)
    Q_PROPERTY(QString not_interested READ not_interested CONSTANT)
    Q_PROPERTY(QString not_listed_location READ not_listed_location CONSTANT)
    Q_PROPERTY(QString note READ note CONSTANT)
    Q_PROPERTY(QString note_add READ note_add CONSTANT)
    Q_PROPERTY(QString notes READ notes CONSTANT)
    Q_PROPERTY(QString notification_important READ notification_important CONSTANT)
    Q_PROPERTY(QString notifications READ notifications CONSTANT)
    Q_PROPERTY(QString notifications_active READ notifications_active CONSTANT)
    Q_PROPERTY(QString notifications_none READ notifications_none CONSTANT)
    Q_PROPERTY(QString notifications_off READ notifications_off CONSTANT)
    Q_PROPERTY(QString notifications_on READ notifications_on CONSTANT)
    Q_PROPERTY(QString notifications_paused READ notifications_paused CONSTANT)
    Q_PROPERTY(QString now_wallpaper READ now_wallpaper CONSTANT)
    Q_PROPERTY(QString now_widgets READ now_widgets CONSTANT)
    Q_PROPERTY(QString offline_bolt READ offline_bolt CONSTANT)
    Q_PROPERTY(QString offline_pin READ offline_pin CONSTANT)
    Q_PROPERTY(QString offline_share READ offline_share CONSTANT)
    Q_PROPERTY(QString ondemand_video READ ondemand_video CONSTANT)
    Q_PROPERTY(QString opacity READ opacity CONSTANT)
    Q_PROPERTY(QString open_in_browser READ open_in_browser CONSTANT)
    Q_PROPERTY(QString open_in_new READ open_in_new CONSTANT)
    Q_PROPERTY(QString open_with READ open_with CONSTANT)
    Q_PROPERTY(QString outdoor_grill READ outdoor_grill CONSTANT)
    Q_PROPERTY(QString outlined_flag READ outlined_flag CONSTANT)
    Q_PROPERTY(QString padding READ padding CONSTANT)
    Q_PROPERTY(QString pages READ pages CONSTANT)
    Q_PROPERTY(QString pageview READ pageview CONSTANT)
    Q_PROPERTY(QString palette READ palette CONSTANT)
    Q_PROPERTY(QString pan_tool READ pan_tool CONSTANT)
    Q_PROPERTY(QString panorama READ panorama CONSTANT)
    Q_PROPERTY(QString panorama_fish_eye READ panorama_fish_eye CONSTANT)
    Q_PROPERTY(QString panorama_fisheye READ panorama_fisheye CONSTANT)
    Q_PROPERTY(QString panorama_horizontal READ panorama_horizontal CONSTANT)
    Q_PROPERTY(QString panorama_photosphere READ panorama_photosphere CONSTANT)
    Q_PROPERTY(QString panorama_photosphere_select READ panorama_photosphere_select CONSTANT)
    Q_PROPERTY(QString panorama_vertical READ panorama_vertical CONSTANT)
    Q_PROPERTY(QString panorama_wide_angle READ panorama_wide_angle CONSTANT)
    Q_PROPERTY(QString park READ park CONSTANT)
    Q_PROPERTY(QString party_mode READ party_mode CONSTANT)
    Q_PROPERTY(QString pause READ pause CONSTANT)
    Q_PROPERTY(QString pause_circle_filled READ pause_circle_filled CONSTANT)
    Q_PROPERTY(QString pause_circle_outline READ pause_circle_outline CONSTANT)
    Q_PROPERTY(QString pause_presentation READ pause_presentation CONSTANT)
    Q_PROPERTY(QString payment READ payment CONSTANT)
    Q_PROPERTY(QString people READ people CONSTANT)
    Q_PROPERTY(QString people_alt READ people_alt CONSTANT)
    Q_PROPERTY(QString people_outline READ people_outline CONSTANT)
    Q_PROPERTY(QString perm_camera_mic READ perm_camera_mic CONSTANT)
    Q_PROPERTY(QString perm_contact_cal READ perm_contact_cal CONSTANT)
    Q_PROPERTY(QString perm_contact_calendar READ perm_contact_calendar CONSTANT)
    Q_PROPERTY(QString perm_data_setting READ perm_data_setting CONSTANT)
    Q_PROPERTY(QString perm_device_info READ perm_device_info CONSTANT)
    Q_PROPERTY(QString perm_device_information READ perm_device_information CONSTANT)
    Q_PROPERTY(QString perm_identity READ perm_identity CONSTANT)
    Q_PROPERTY(QString perm_media READ perm_media CONSTANT)
    Q_PROPERTY(QString perm_phone_msg READ perm_phone_msg CONSTANT)
    Q_PROPERTY(QString perm_scan_wifi READ perm_scan_wifi CONSTANT)
    Q_PROPERTY(QString person READ person CONSTANT)
    Q_PROPERTY(QString person_add READ person_add CONSTANT)
    Q_PROPERTY(QString person_add_disabled READ person_add_disabled CONSTANT)
    Q_PROPERTY(QString person_outline READ person_outline CONSTANT)
    Q_PROPERTY(QString person_pin READ person_pin CONSTANT)
    Q_PROPERTY(QString person_pin_circle READ person_pin_circle CONSTANT)
    Q_PROPERTY(QString personal_video READ personal_video CONSTANT)
    Q_PROPERTY(QString pets READ pets CONSTANT)
    Q_PROPERTY(QString phone READ phone CONSTANT)
    Q_PROPERTY(QString phone_android READ phone_android CONSTANT)
    Q_PROPERTY(QString phone_bluetooth_speaker READ phone_bluetooth_speaker CONSTANT)
    Q_PROPERTY(QString phone_callback READ phone_callback CONSTANT)
    Q_PROPERTY(QString phone_disabled READ phone_disabled CONSTANT)
    Q_PROPERTY(QString phone_enabled READ phone_enabled CONSTANT)
    Q_PROPERTY(QString phone_forwarded READ phone_forwarded CONSTANT)
    Q_PROPERTY(QString phone_in_talk READ phone_in_talk CONSTANT)
    Q_PROPERTY(QString phone_iphone READ phone_iphone CONSTANT)
    Q_PROPERTY(QString phone_locked READ phone_locked CONSTANT)
    Q_PROPERTY(QString phone_missed READ phone_missed CONSTANT)
    Q_PROPERTY(QString phone_paused READ phone_paused CONSTANT)
    Q_PROPERTY(QString phonelink READ phonelink CONSTANT)
    Q_PROPERTY(QString phonelink_erase READ phonelink_erase CONSTANT)
    Q_PROPERTY(QString phonelink_lock READ phonelink_lock CONSTANT)
    Q_PROPERTY(QString phonelink_off READ phonelink_off CONSTANT)
    Q_PROPERTY(QString phonelink_ring READ phonelink_ring CONSTANT)
    Q_PROPERTY(QString phonelink_setup READ phonelink_setup CONSTANT)
    Q_PROPERTY(QString photo READ photo CONSTANT)
    Q_PROPERTY(QString photo_album READ photo_album CONSTANT)
    Q_PROPERTY(QString photo_camera READ photo_camera CONSTANT)
    Q_PROPERTY(QString photo_filter READ photo_filter CONSTANT)
    Q_PROPERTY(QString photo_library READ photo_library CONSTANT)
    Q_PROPERTY(QString photo_size_select_actual READ photo_size_select_actual CONSTANT)
    Q_PROPERTY(QString photo_size_select_large READ photo_size_select_large CONSTANT)
    Q_PROPERTY(QString photo_size_select_small READ photo_size_select_small CONSTANT)
    Q_PROPERTY(QString picture_as_pdf READ picture_as_pdf CONSTANT)
    Q_PROPERTY(QString picture_in_picture READ picture_in_picture CONSTANT)
    Q_PROPERTY(QString picture_in_picture_alt READ picture_in_picture_alt CONSTANT)
    Q_PROPERTY(QString pie_chart READ pie_chart CONSTANT)
    Q_PROPERTY(QString pie_chart_outlined READ pie_chart_outlined CONSTANT)
    Q_PROPERTY(QString pin_drop READ pin_drop CONSTANT)
    Q_PROPERTY(QString pivot_table_chart READ pivot_table_chart CONSTANT)
    Q_PROPERTY(QString place READ place CONSTANT)
    Q_PROPERTY(QString play_arrow READ play_arrow CONSTANT)
    Q_PROPERTY(QString play_circle_fill READ play_circle_fill CONSTANT)
    Q_PROPERTY(QString play_circle_filled READ play_circle_filled CONSTANT)
    Q_PROPERTY(QString play_circle_outline READ play_circle_outline CONSTANT)
    Q_PROPERTY(QString play_for_work READ play_for_work CONSTANT)
    Q_PROPERTY(QString playlist_add READ playlist_add CONSTANT)
    Q_PROPERTY(QString playlist_add_check READ playlist_add_check CONSTANT)
    Q_PROPERTY(QString playlist_play READ playlist_play CONSTANT)
    Q_PROPERTY(QString plus_one READ plus_one CONSTANT)
    Q_PROPERTY(QString policy READ policy CONSTANT)
    Q_PROPERTY(QString poll READ poll CONSTANT)
    Q_PROPERTY(QString polymer READ polymer CONSTANT)
    Q_PROPERTY(QString pool READ pool CONSTANT)
    Q_PROPERTY(QString portable_wifi_off READ portable_wifi_off CONSTANT)
    Q_PROPERTY(QString portrait READ portrait CONSTANT)
    Q_PROPERTY(QString post_add READ post_add CONSTANT)
    Q_PROPERTY(QString power READ power CONSTANT)
    Q_PROPERTY(QString power_input READ power_input CONSTANT)
    Q_PROPERTY(QString power_off READ power_off CONSTANT)
    Q_PROPERTY(QString power_settings_new READ power_settings_new CONSTANT)
    Q_PROPERTY(QString pregnant_woman READ pregnant_woman CONSTANT)
    Q_PROPERTY(QString present_to_all READ present_to_all CONSTANT)
    Q_PROPERTY(QString print READ print CONSTANT)
    Q_PROPERTY(QString print_disabled READ print_disabled CONSTANT)
    Q_PROPERTY(QString priority_high READ priority_high CONSTANT)
    Q_PROPERTY(QString publish READ publish CONSTANT)
    Q_PROPERTY(QString query_builder READ query_builder CONSTANT)
    Q_PROPERTY(QString question_answer READ question_answer CONSTANT)
    Q_PROPERTY(QString queue READ queue CONSTANT)
    Q_PROPERTY(QString queue_music READ queue_music CONSTANT)
    Q_PROPERTY(QString queue_play_next READ queue_play_next CONSTANT)
    Q_PROPERTY(QString quick_contacts_dialer READ quick_contacts_dialer CONSTANT)
    Q_PROPERTY(QString quick_contacts_mail READ quick_contacts_mail CONSTANT)
    Q_PROPERTY(QString radio READ radio CONSTANT)
    Q_PROPERTY(QString radio_button_checked READ radio_button_checked CONSTANT)
    Q_PROPERTY(QString radio_button_off READ radio_button_off CONSTANT)
    Q_PROPERTY(QString radio_button_on READ radio_button_on CONSTANT)
    Q_PROPERTY(QString radio_button_unchecked READ radio_button_unchecked CONSTANT)
    Q_PROPERTY(QString railway_alert READ railway_alert CONSTANT)
    Q_PROPERTY(QString ramen_dining READ ramen_dining CONSTANT)
    Q_PROPERTY(QString rate_review READ rate_review CONSTANT)
    Q_PROPERTY(QString receipt READ receipt CONSTANT)
    Q_PROPERTY(QString recent_actors READ recent_actors CONSTANT)
    Q_PROPERTY(QString recommend READ recommend CONSTANT)
    Q_PROPERTY(QString record_voice_over READ record_voice_over CONSTANT)
    Q_PROPERTY(QString redeem READ redeem CONSTANT)
    Q_PROPERTY(QString redo READ redo CONSTANT)
    Q_PROPERTY(QString refresh READ refresh CONSTANT)
    Q_PROPERTY(QString remove READ remove CONSTANT)
    Q_PROPERTY(QString remove_circle READ remove_circle CONSTANT)
    Q_PROPERTY(QString remove_circle_outline READ remove_circle_outline CONSTANT)
    Q_PROPERTY(QString remove_done READ remove_done CONSTANT)
    Q_PROPERTY(QString remove_from_queue READ remove_from_queue CONSTANT)
    Q_PROPERTY(QString remove_moderator READ remove_moderator CONSTANT)
    Q_PROPERTY(QString remove_red_eye READ remove_red_eye CONSTANT)
    Q_PROPERTY(QString remove_shopping_cart READ remove_shopping_cart CONSTANT)
    Q_PROPERTY(QString reorder READ reorder CONSTANT)
    Q_PROPERTY(QString repeat READ repeat CONSTANT)
    Q_PROPERTY(QString repeat_on READ repeat_on CONSTANT)
    Q_PROPERTY(QString repeat_one READ repeat_one CONSTANT)
    Q_PROPERTY(QString repeat_one_on READ repeat_one_on CONSTANT)
    Q_PROPERTY(QString replay READ replay CONSTANT)
    Q_PROPERTY(QString replay_10 READ replay_10 CONSTANT)
    Q_PROPERTY(QString replay_30 READ replay_30 CONSTANT)
    Q_PROPERTY(QString replay_5 READ replay_5 CONSTANT)
    Q_PROPERTY(QString replay_circle_filled READ replay_circle_filled CONSTANT)
    Q_PROPERTY(QString reply READ reply CONSTANT)
    Q_PROPERTY(QString reply_all READ reply_all CONSTANT)
    Q_PROPERTY(QString report READ report CONSTANT)
    Q_PROPERTY(QString report_off READ report_off CONSTANT)
    Q_PROPERTY(QString report_problem READ report_problem CONSTANT)
    Q_PROPERTY(QString reset_tv READ reset_tv CONSTANT)
    Q_PROPERTY(QString restaurant READ restaurant CONSTANT)
    Q_PROPERTY(QString restaurant_menu READ restaurant_menu CONSTANT)
    Q_PROPERTY(QString restore READ restore CONSTANT)
    Q_PROPERTY(QString restore_from_trash READ restore_from_trash CONSTANT)
    Q_PROPERTY(QString restore_page READ restore_page CONSTANT)
    Q_PROPERTY(QString ring_volume READ ring_volume CONSTANT)
    Q_PROPERTY(QString room READ room CONSTANT)
    Q_PROPERTY(QString room_service READ room_service CONSTANT)
    Q_PROPERTY(QString rotate_90_degrees_ccw READ rotate_90_degrees_ccw CONSTANT)
    Q_PROPERTY(QString rotate_left READ rotate_left CONSTANT)
    Q_PROPERTY(QString rotate_right READ rotate_right CONSTANT)
    Q_PROPERTY(QString rounded_corner READ rounded_corner CONSTANT)
    Q_PROPERTY(QString router READ router CONSTANT)
    Q_PROPERTY(QString rowing READ rowing CONSTANT)
    Q_PROPERTY(QString rss_feed READ rss_feed CONSTANT)
    Q_PROPERTY(QString rtt READ rtt CONSTANT)
    Q_PROPERTY(QString rv_hookup READ rv_hookup CONSTANT)
    Q_PROPERTY(QString satellite READ satellite CONSTANT)
    Q_PROPERTY(QString save READ save CONSTANT)
    Q_PROPERTY(QString save_alt READ save_alt CONSTANT)
    Q_PROPERTY(QString saved_search READ saved_search CONSTANT)
    Q_PROPERTY(QString scanner READ scanner CONSTANT)
    Q_PROPERTY(QString scatter_plot READ scatter_plot CONSTANT)
    Q_PROPERTY(QString schedule READ schedule CONSTANT)
    Q_PROPERTY(QString schedule_send READ schedule_send CONSTANT)
    Q_PROPERTY(QString school READ school CONSTANT)
    Q_PROPERTY(QString score READ score CONSTANT)
    Q_PROPERTY(QString screen_lock_landscape READ screen_lock_landscape CONSTANT)
    Q_PROPERTY(QString screen_lock_portrait READ screen_lock_portrait CONSTANT)
    Q_PROPERTY(QString screen_lock_rotation READ screen_lock_rotation CONSTANT)
    Q_PROPERTY(QString screen_rotation READ screen_rotation CONSTANT)
    Q_PROPERTY(QString screen_share READ screen_share CONSTANT)
    Q_PROPERTY(QString sd READ sd CONSTANT)
    Q_PROPERTY(QString sd_card READ sd_card CONSTANT)
    Q_PROPERTY(QString sd_storage READ sd_storage CONSTANT)
    Q_PROPERTY(QString search READ search CONSTANT)
    Q_PROPERTY(QString security READ security CONSTANT)
    Q_PROPERTY(QString segment READ segment CONSTANT)
    Q_PROPERTY(QString select_all READ select_all CONSTANT)
    Q_PROPERTY(QString send READ send CONSTANT)
    Q_PROPERTY(QString send_and_archive READ send_and_archive CONSTANT)
    Q_PROPERTY(QString sentiment_dissatisfied READ sentiment_dissatisfied CONSTANT)
    Q_PROPERTY(QString sentiment_neutral READ sentiment_neutral CONSTANT)
    Q_PROPERTY(QString sentiment_satisfied READ sentiment_satisfied CONSTANT)
    Q_PROPERTY(QString sentiment_satisfied_alt READ sentiment_satisfied_alt CONSTANT)
    Q_PROPERTY(QString sentiment_very_dissatisfied READ sentiment_very_dissatisfied CONSTANT)
    Q_PROPERTY(QString sentiment_very_satisfied READ sentiment_very_satisfied CONSTANT)
    Q_PROPERTY(QString settings READ settings CONSTANT)
    Q_PROPERTY(QString settings_applications READ settings_applications CONSTANT)
    Q_PROPERTY(QString settings_backup_restore READ settings_backup_restore CONSTANT)
    Q_PROPERTY(QString settings_bluetooth READ settings_bluetooth CONSTANT)
    Q_PROPERTY(QString settings_brightness READ settings_brightness CONSTANT)
    Q_PROPERTY(QString settings_cell READ settings_cell CONSTANT)
    Q_PROPERTY(QString settings_display READ settings_display CONSTANT)
    Q_PROPERTY(QString settings_ethernet READ settings_ethernet CONSTANT)
    Q_PROPERTY(QString settings_input_antenna READ settings_input_antenna CONSTANT)
    Q_PROPERTY(QString settings_input_component READ settings_input_component CONSTANT)
    Q_PROPERTY(QString settings_input_composite READ settings_input_composite CONSTANT)
    Q_PROPERTY(QString settings_input_hdmi READ settings_input_hdmi CONSTANT)
    Q_PROPERTY(QString settings_input_svideo READ settings_input_svideo CONSTANT)
    Q_PROPERTY(QString settings_overscan READ settings_overscan CONSTANT)
    Q_PROPERTY(QString settings_phone READ settings_phone CONSTANT)
    Q_PROPERTY(QString settings_power READ settings_power CONSTANT)
    Q_PROPERTY(QString settings_remote READ settings_remote CONSTANT)
    Q_PROPERTY(QString settings_system_daydream READ settings_system_daydream CONSTANT)
    Q_PROPERTY(QString settings_voice READ settings_voice CONSTANT)
    Q_PROPERTY(QString share READ share CONSTANT)
    Q_PROPERTY(QString shield READ shield CONSTANT)
    Q_PROPERTY(QString shop READ shop CONSTANT)
    Q_PROPERTY(QString shop_two READ shop_two CONSTANT)
    Q_PROPERTY(QString shopping_basket READ shopping_basket CONSTANT)
    Q_PROPERTY(QString shopping_cart READ shopping_cart CONSTANT)
    Q_PROPERTY(QString short_text READ short_text CONSTANT)
    Q_PROPERTY(QString show_chart READ show_chart CONSTANT)
    Q_PROPERTY(QString shuffle READ shuffle CONSTANT)
    Q_PROPERTY(QString shuffle_on READ shuffle_on CONSTANT)
    Q_PROPERTY(QString shutter_speed READ shutter_speed CONSTANT)
    Q_PROPERTY(QString signal_cellular_4_bar READ signal_cellular_4_bar CONSTANT)
    Q_PROPERTY(QString signal_cellular_alt READ signal_cellular_alt CONSTANT)
    Q_PROPERTY(QString signal_cellular_connected_no_internet_4_bar READ signal_cellular_connected_no_internet_4_bar CONSTANT)
    Q_PROPERTY(QString signal_cellular_no_sim READ signal_cellular_no_sim CONSTANT)
    Q_PROPERTY(QString signal_cellular_null READ signal_cellular_null CONSTANT)
    Q_PROPERTY(QString signal_cellular_off READ signal_cellular_off CONSTANT)
    Q_PROPERTY(QString signal_wifi_4_bar READ signal_wifi_4_bar CONSTANT)
    Q_PROPERTY(QString signal_wifi_4_bar_lock READ signal_wifi_4_bar_lock CONSTANT)
    Q_PROPERTY(QString signal_wifi_off READ signal_wifi_off CONSTANT)
    Q_PROPERTY(QString sim_card READ sim_card CONSTANT)
    Q_PROPERTY(QString sim_card_alert READ sim_card_alert CONSTANT)
    Q_PROPERTY(QString single_bed READ single_bed CONSTANT)
    Q_PROPERTY(QString skip_next READ skip_next CONSTANT)
    Q_PROPERTY(QString skip_previous READ skip_previous CONSTANT)
    Q_PROPERTY(QString slideshow READ slideshow CONSTANT)
    Q_PROPERTY(QString slow_motion_video READ slow_motion_video CONSTANT)
    Q_PROPERTY(QString smartphone READ smartphone CONSTANT)
    Q_PROPERTY(QString smoke_free READ smoke_free CONSTANT)
    Q_PROPERTY(QString smoking_rooms READ smoking_rooms CONSTANT)
    Q_PROPERTY(QString sms READ sms CONSTANT)
    Q_PROPERTY(QString sms_failed READ sms_failed CONSTANT)
    Q_PROPERTY(QString snooze READ snooze CONSTANT)
    Q_PROPERTY(QString sort READ sort CONSTANT)
    Q_PROPERTY(QString sort_by_alpha READ sort_by_alpha CONSTANT)
    Q_PROPERTY(QString spa READ spa CONSTANT)
    Q_PROPERTY(QString space_bar READ space_bar CONSTANT)
    Q_PROPERTY(QString speaker READ speaker CONSTANT)
    Q_PROPERTY(QString speaker_group READ speaker_group CONSTANT)
    Q_PROPERTY(QString speaker_notes READ speaker_notes CONSTANT)
    Q_PROPERTY(QString speaker_notes_off READ speaker_notes_off CONSTANT)
    Q_PROPERTY(QString speaker_phone READ speaker_phone CONSTANT)
    Q_PROPERTY(QString speed READ speed CONSTANT)
    Q_PROPERTY(QString spellcheck READ spellcheck CONSTANT)
    Q_PROPERTY(QString sports READ sports CONSTANT)
    Q_PROPERTY(QString sports_baseball READ sports_baseball CONSTANT)
    Q_PROPERTY(QString sports_basketball READ sports_basketball CONSTANT)
    Q_PROPERTY(QString sports_cricket READ sports_cricket CONSTANT)
    Q_PROPERTY(QString sports_esports READ sports_esports CONSTANT)
    Q_PROPERTY(QString sports_football READ sports_football CONSTANT)
    Q_PROPERTY(QString sports_golf READ sports_golf CONSTANT)
    Q_PROPERTY(QString sports_handball READ sports_handball CONSTANT)
    Q_PROPERTY(QString sports_hockey READ sports_hockey CONSTANT)
    Q_PROPERTY(QString sports_kabaddi READ sports_kabaddi CONSTANT)
    Q_PROPERTY(QString sports_mma READ sports_mma CONSTANT)
    Q_PROPERTY(QString sports_motorsports READ sports_motorsports CONSTANT)
    Q_PROPERTY(QString sports_rugby READ sports_rugby CONSTANT)
    Q_PROPERTY(QString sports_soccer READ sports_soccer CONSTANT)
    Q_PROPERTY(QString sports_tennis READ sports_tennis CONSTANT)
    Q_PROPERTY(QString sports_volleyball READ sports_volleyball CONSTANT)
    Q_PROPERTY(QString square_foot READ square_foot CONSTANT)
    Q_PROPERTY(QString stacked_bar_chart READ stacked_bar_chart CONSTANT)
    Q_PROPERTY(QString star READ star CONSTANT)
    Q_PROPERTY(QString star_border READ star_border CONSTANT)
    Q_PROPERTY(QString star_half READ star_half CONSTANT)
    Q_PROPERTY(QString star_outline READ star_outline CONSTANT)
    Q_PROPERTY(QString stars READ stars CONSTANT)
    Q_PROPERTY(QString stay_current_landscape READ stay_current_landscape CONSTANT)
    Q_PROPERTY(QString stay_current_portrait READ stay_current_portrait CONSTANT)
    Q_PROPERTY(QString stay_primary_landscape READ stay_primary_landscape CONSTANT)
    Q_PROPERTY(QString stay_primary_portrait READ stay_primary_portrait CONSTANT)
    Q_PROPERTY(QString stop READ stop CONSTANT)
    Q_PROPERTY(QString stop_screen_share READ stop_screen_share CONSTANT)
    Q_PROPERTY(QString storage READ storage CONSTANT)
    Q_PROPERTY(QString store READ store CONSTANT)
    Q_PROPERTY(QString store_mall_directory READ store_mall_directory CONSTANT)
    Q_PROPERTY(QString storefront READ storefront CONSTANT)
    Q_PROPERTY(QString straighten READ straighten CONSTANT)
    Q_PROPERTY(QString stream READ stream CONSTANT)
    Q_PROPERTY(QString streetview READ streetview CONSTANT)
    Q_PROPERTY(QString strikethrough_s READ strikethrough_s CONSTANT)
    Q_PROPERTY(QString style READ style CONSTANT)
    Q_PROPERTY(QString subdirectory_arrow_left READ subdirectory_arrow_left CONSTANT)
    Q_PROPERTY(QString subdirectory_arrow_right READ subdirectory_arrow_right CONSTANT)
    Q_PROPERTY(QString subject READ subject CONSTANT)
    Q_PROPERTY(QString subscriptions READ subscriptions CONSTANT)
    Q_PROPERTY(QString subtitles READ subtitles CONSTANT)
    Q_PROPERTY(QString subway READ subway CONSTANT)
    Q_PROPERTY(QString supervised_user_circle READ supervised_user_circle CONSTANT)
    Q_PROPERTY(QString supervisor_account READ supervisor_account CONSTANT)
    Q_PROPERTY(QString surround_sound READ surround_sound CONSTANT)
    Q_PROPERTY(QString swap_calls READ swap_calls CONSTANT)
    Q_PROPERTY(QString swap_horiz READ swap_horiz CONSTANT)
    Q_PROPERTY(QString swap_horizontal_circle READ swap_horizontal_circle CONSTANT)
    Q_PROPERTY(QString swap_vert READ swap_vert CONSTANT)
    Q_PROPERTY(QString swap_vert_circle READ swap_vert_circle CONSTANT)
    Q_PROPERTY(QString swap_vertical_circle READ swap_vertical_circle CONSTANT)
    Q_PROPERTY(QString swipe READ swipe CONSTANT)
    Q_PROPERTY(QString switch_account READ switch_account CONSTANT)
    Q_PROPERTY(QString switch_camera READ switch_camera CONSTANT)
    Q_PROPERTY(QString switch_video READ switch_video CONSTANT)
    Q_PROPERTY(QString sync READ sync CONSTANT)
    Q_PROPERTY(QString sync_alt READ sync_alt CONSTANT)
    Q_PROPERTY(QString sync_disabled READ sync_disabled CONSTANT)
    Q_PROPERTY(QString sync_problem READ sync_problem CONSTANT)
    Q_PROPERTY(QString system_update READ system_update CONSTANT)
    Q_PROPERTY(QString system_update_alt READ system_update_alt CONSTANT)
    Q_PROPERTY(QString system_update_tv READ system_update_tv CONSTANT)
    Q_PROPERTY(QString tab READ tab CONSTANT)
    Q_PROPERTY(QString tab_unselected READ tab_unselected CONSTANT)
    Q_PROPERTY(QString table_chart READ table_chart CONSTANT)
    Q_PROPERTY(QString tablet READ tablet CONSTANT)
    Q_PROPERTY(QString tablet_android READ tablet_android CONSTANT)
    Q_PROPERTY(QString tablet_mac READ tablet_mac CONSTANT)
    Q_PROPERTY(QString tag READ tag CONSTANT)
    Q_PROPERTY(QString tag_faces READ tag_faces CONSTANT)
    Q_PROPERTY(QString takeout_dining READ takeout_dining CONSTANT)
    Q_PROPERTY(QString tap_and_play READ tap_and_play CONSTANT)
    Q_PROPERTY(QString terrain READ terrain CONSTANT)
    Q_PROPERTY(QString text_fields READ text_fields CONSTANT)
    Q_PROPERTY(QString text_format READ text_format CONSTANT)
    Q_PROPERTY(QString text_rotate_up READ text_rotate_up CONSTANT)
    Q_PROPERTY(QString text_rotate_vertical READ text_rotate_vertical CONSTANT)
    Q_PROPERTY(QString text_rotation_angledown READ text_rotation_angledown CONSTANT)
    Q_PROPERTY(QString text_rotation_angleup READ text_rotation_angleup CONSTANT)
    Q_PROPERTY(QString text_rotation_down READ text_rotation_down CONSTANT)
    Q_PROPERTY(QString text_rotation_none READ text_rotation_none CONSTANT)
    Q_PROPERTY(QString textsms READ textsms CONSTANT)
    Q_PROPERTY(QString texture READ texture CONSTANT)
    Q_PROPERTY(QString theater_comedy READ theater_comedy CONSTANT)
    Q_PROPERTY(QString theaters READ theaters CONSTANT)
    Q_PROPERTY(QString thumb_down READ thumb_down CONSTANT)
    Q_PROPERTY(QString thumb_down_alt READ thumb_down_alt CONSTANT)
    Q_PROPERTY(QString thumb_down_off_alt READ thumb_down_off_alt CONSTANT)
    Q_PROPERTY(QString thumb_up READ thumb_up CONSTANT)
    Q_PROPERTY(QString thumb_up_alt READ thumb_up_alt CONSTANT)
    Q_PROPERTY(QString thumb_up_off_alt READ thumb_up_off_alt CONSTANT)
    Q_PROPERTY(QString thumbs_up_down READ thumbs_up_down CONSTANT)
    Q_PROPERTY(QString time_to_leave READ time_to_leave CONSTANT)
    Q_PROPERTY(QString timelapse READ timelapse CONSTANT)
    Q_PROPERTY(QString timeline READ timeline CONSTANT)
    Q_PROPERTY(QString timer READ timer CONSTANT)
    Q_PROPERTY(QString timer_10 READ timer_10 CONSTANT)
    Q_PROPERTY(QString timer_3 READ timer_3 CONSTANT)
    Q_PROPERTY(QString timer_off READ timer_off CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString toc READ toc CONSTANT)
    Q_PROPERTY(QString today READ today CONSTANT)
    Q_PROPERTY(QString toggle_off READ toggle_off CONSTANT)
    Q_PROPERTY(QString toggle_on READ toggle_on CONSTANT)
    Q_PROPERTY(QString toll READ toll CONSTANT)
    Q_PROPERTY(QString tonality READ tonality CONSTANT)
    Q_PROPERTY(QString touch_app READ touch_app CONSTANT)
    Q_PROPERTY(QString toys READ toys CONSTANT)
    Q_PROPERTY(QString track_changes READ track_changes CONSTANT)
    Q_PROPERTY(QString traffic READ traffic CONSTANT)
    Q_PROPERTY(QString train READ train CONSTANT)
    Q_PROPERTY(QString tram READ tram CONSTANT)
    Q_PROPERTY(QString transfer_within_a_station READ transfer_within_a_station CONSTANT)
    Q_PROPERTY(QString transform READ transform CONSTANT)
    Q_PROPERTY(QString transit_enterexit READ transit_enterexit CONSTANT)
    Q_PROPERTY(QString translate READ translate CONSTANT)
    Q_PROPERTY(QString trending_down READ trending_down CONSTANT)
    Q_PROPERTY(QString trending_flat READ trending_flat CONSTANT)
    Q_PROPERTY(QString trending_neutral READ trending_neutral CONSTANT)
    Q_PROPERTY(QString trending_up READ trending_up CONSTANT)
    Q_PROPERTY(QString trip_origin READ trip_origin CONSTANT)
    Q_PROPERTY(QString tune READ tune CONSTANT)
    Q_PROPERTY(QString turned_in READ turned_in CONSTANT)
    Q_PROPERTY(QString turned_in_not READ turned_in_not CONSTANT)
    Q_PROPERTY(QString tv READ tv CONSTANT)
    Q_PROPERTY(QString tv_off READ tv_off CONSTANT)
    Q_PROPERTY(QString two_wheeler READ two_wheeler CONSTANT)
    Q_PROPERTY(QString unarchive READ unarchive CONSTANT)
    Q_PROPERTY(QString undo READ undo CONSTANT)
    Q_PROPERTY(QString unfold_less READ unfold_less CONSTANT)
    Q_PROPERTY(QString unfold_more READ unfold_more CONSTANT)
    Q_PROPERTY(QString unsubscribe READ unsubscribe CONSTANT)
    Q_PROPERTY(QString update READ update CONSTANT)
    Q_PROPERTY(QString upload_file READ upload_file CONSTANT)
    Q_PROPERTY(QString usb READ usb CONSTANT)
    Q_PROPERTY(QString verified_user READ verified_user CONSTANT)
    Q_PROPERTY(QString vertical_align_bottom READ vertical_align_bottom CONSTANT)
    Q_PROPERTY(QString vertical_align_center READ vertical_align_center CONSTANT)
    Q_PROPERTY(QString vertical_align_top READ vertical_align_top CONSTANT)
    Q_PROPERTY(QString vertical_split READ vertical_split CONSTANT)
    Q_PROPERTY(QString vibration READ vibration CONSTANT)
    Q_PROPERTY(QString video_call READ video_call CONSTANT)
    Q_PROPERTY(QString video_collection READ video_collection CONSTANT)
    Q_PROPERTY(QString video_label READ video_label CONSTANT)
    Q_PROPERTY(QString video_library READ video_library CONSTANT)
    Q_PROPERTY(QString videocam READ videocam CONSTANT)
    Q_PROPERTY(QString videocam_off READ videocam_off CONSTANT)
    Q_PROPERTY(QString videogame_asset READ videogame_asset CONSTANT)
    Q_PROPERTY(QString view_agenda READ view_agenda CONSTANT)
    Q_PROPERTY(QString view_array READ view_array CONSTANT)
    Q_PROPERTY(QString view_carousel READ view_carousel CONSTANT)
    Q_PROPERTY(QString view_column READ view_column CONSTANT)
    Q_PROPERTY(QString view_comfortable READ view_comfortable CONSTANT)
    Q_PROPERTY(QString view_comfy READ view_comfy CONSTANT)
    Q_PROPERTY(QString view_compact READ view_compact CONSTANT)
    Q_PROPERTY(QString view_day READ view_day CONSTANT)
    Q_PROPERTY(QString view_headline READ view_headline CONSTANT)
    Q_PROPERTY(QString view_in_ar READ view_in_ar CONSTANT)
    Q_PROPERTY(QString view_list READ view_list CONSTANT)
    Q_PROPERTY(QString view_module READ view_module CONSTANT)
    Q_PROPERTY(QString view_quilt READ view_quilt CONSTANT)
    Q_PROPERTY(QString view_stream READ view_stream CONSTANT)
    Q_PROPERTY(QString view_week READ view_week CONSTANT)
    Q_PROPERTY(QString vignette READ vignette CONSTANT)
    Q_PROPERTY(QString visibility READ visibility CONSTANT)
    Q_PROPERTY(QString visibility_off READ visibility_off CONSTANT)
    Q_PROPERTY(QString voice_chat READ voice_chat CONSTANT)
    Q_PROPERTY(QString voice_over_off READ voice_over_off CONSTANT)
    Q_PROPERTY(QString voicemail READ voicemail CONSTANT)
    Q_PROPERTY(QString volume_down READ volume_down CONSTANT)
    Q_PROPERTY(QString volume_mute READ volume_mute CONSTANT)
    Q_PROPERTY(QString volume_off READ volume_off CONSTANT)
    Q_PROPERTY(QString volume_up READ volume_up CONSTANT)
    Q_PROPERTY(QString volunteer_activism READ volunteer_activism CONSTANT)
    Q_PROPERTY(QString vpn_key READ vpn_key CONSTANT)
    Q_PROPERTY(QString vpn_lock READ vpn_lock CONSTANT)
    Q_PROPERTY(QString wallet_giftcard READ wallet_giftcard CONSTANT)
    Q_PROPERTY(QString wallet_membership READ wallet_membership CONSTANT)
    Q_PROPERTY(QString wallet_travel READ wallet_travel CONSTANT)
    Q_PROPERTY(QString wallpaper READ wallpaper CONSTANT)
    Q_PROPERTY(QString warning READ warning CONSTANT)
    Q_PROPERTY(QString watch READ watch CONSTANT)
    Q_PROPERTY(QString watch_later READ watch_later CONSTANT)
    Q_PROPERTY(QString waterfall_chart READ waterfall_chart CONSTANT)
    Q_PROPERTY(QString waves READ waves CONSTANT)
    Q_PROPERTY(QString wb_auto READ wb_auto CONSTANT)
    Q_PROPERTY(QString wb_cloudy READ wb_cloudy CONSTANT)
    Q_PROPERTY(QString wb_incandescent READ wb_incandescent CONSTANT)
    Q_PROPERTY(QString wb_iridescent READ wb_iridescent CONSTANT)
    Q_PROPERTY(QString wb_shade READ wb_shade CONSTANT)
    Q_PROPERTY(QString wb_sunny READ wb_sunny CONSTANT)
    Q_PROPERTY(QString wb_twighlight READ wb_twighlight CONSTANT)
    Q_PROPERTY(QString wc READ wc CONSTANT)
    Q_PROPERTY(QString web READ web CONSTANT)
    Q_PROPERTY(QString web_asset READ web_asset CONSTANT)
    Q_PROPERTY(QString weekend READ weekend CONSTANT)
    Q_PROPERTY(QString whatshot READ whatshot CONSTANT)
    Q_PROPERTY(QString where_to_vote READ where_to_vote CONSTANT)
    Q_PROPERTY(QString widgets READ widgets CONSTANT)
    Q_PROPERTY(QString wifi READ wifi CONSTANT)
    Q_PROPERTY(QString wifi_lock READ wifi_lock CONSTANT)
    Q_PROPERTY(QString wifi_off READ wifi_off CONSTANT)
    Q_PROPERTY(QString wifi_tethering READ wifi_tethering CONSTANT)
    Q_PROPERTY(QString work READ work CONSTANT)
    Q_PROPERTY(QString work_off READ work_off CONSTANT)
    Q_PROPERTY(QString work_outline READ work_outline CONSTANT)
    Q_PROPERTY(QString workspaces_filled READ workspaces_filled CONSTANT)
    Q_PROPERTY(QString workspaces_outline READ workspaces_outline CONSTANT)
    Q_PROPERTY(QString wrap_text READ wrap_text CONSTANT)
    Q_PROPERTY(QString youtube_searched_for READ youtube_searched_for CONSTANT)
    Q_PROPERTY(QString zoom_in READ zoom_in CONSTANT)
    Q_PROPERTY(QString zoom_out READ zoom_out CONSTANT)
    Q_PROPERTY(QString zoom_out_map READ zoom_out_map CONSTANT)

public:
    explicit Material(QObject *parent = nullptr);

    QColor red() const { return color(Red); }
    QColor pink() const { return color(Pink); }
    QColor purple() const { return color(Purple); }
    QColor deepPurple() const { return color(DeepPurple); }
    QColor indigo() const { return color(Indigo); }
    QColor blue() const { return color(Blue); }
    QColor lightBlue() const { return color(LightBlue); }
    QColor cyan() const { return color(Cyan); }
    QColor teal() const { return color(Teal); }
    QColor green() const { return color(Green); }
    QColor lightGreen() const { return color(LightGreen); }
    QColor lime() const { return color(Lime); }
    QColor yellow() const { return color(Yellow); }
    QColor amber() const { return color(Amber); }
    QColor orange() const { return color(Orange); }
    QColor deepOrange() const { return color(DeepOrange); }
    QColor brown() const { return color(Brown); }
    QColor gray() const { return color(Gray); }
    QColor blueGray() const { return color(BlueGray); }

    enum Color {
        Red,
        Pink,
        Purple,
        DeepPurple,
        Indigo,
        Blue,
        LightBlue,
        Cyan,
        Teal,
        Green,
        LightGreen,
        Lime,
        Yellow,
        Amber,
        Orange,
        DeepOrange,
        Brown,
        Gray,
        BlueGray
    };
    Q_ENUM(Color)

    enum Shade {
        Shade50,
        Shade100,
        Shade200,
        Shade300,
        Shade400,
        Shade500,
        Shade600,
        Shade700,
        Shade800,
        Shade900,
        ShadeA100,
        ShadeA200,
        ShadeA400,
        ShadeA700,
    };
    Q_ENUM(Shade)

    Shade shade() const;
    void setShade(Shade shade);

    Q_INVOKABLE QColor color(Color color) const;
    Q_INVOKABLE QColor color(Color color, Shade shade) const;

    static QString fontFamily();
    static QString _10k() { return "\ue951"; }
    static QString _10mp() { return "\ue952"; }
    static QString _11mp() { return "\ue953"; }
    static QString _12mp() { return "\ue954"; }
    static QString _13mp() { return "\ue955"; }
    static QString _14mp() { return "\ue956"; }
    static QString _15mp() { return "\ue957"; }
    static QString _16mp() { return "\ue958"; }
    static QString _17mp() { return "\ue959"; }
    static QString _18mp() { return "\ue95a"; }
    static QString _19mp() { return "\ue95b"; }
    static QString _1k() { return "\ue95c"; }
    static QString _1k_plus() { return "\ue95d"; }
    static QString _20mp() { return "\ue95e"; }
    static QString _21mp() { return "\ue95f"; }
    static QString _22mp() { return "\ue960"; }
    static QString _23mp() { return "\ue961"; }
    static QString _24mp() { return "\ue962"; }
    static QString _2k() { return "\ue963"; }
    static QString _2k_plus() { return "\ue964"; }
    static QString _2mp() { return "\ue965"; }
    static QString _360() { return "\ue577"; }
    static QString _3d_rotation() { return "\ue84d"; }
    static QString _3k() { return "\ue966"; }
    static QString _3k_plus() { return "\ue967"; }
    static QString _3mp() { return "\ue968"; }
    static QString _4k() { return "\ue072"; }
    static QString _4k_plus() { return "\ue969"; }
    static QString _4mp() { return "\ue96a"; }
    static QString _5k() { return "\ue96b"; }
    static QString _5k_plus() { return "\ue96c"; }
    static QString _5mp() { return "\ue96d"; }
    static QString _6k() { return "\ue96e"; }
    static QString _6k_plus() { return "\ue96f"; }
    static QString _6mp() { return "\ue970"; }
    static QString _7k() { return "\ue971"; }
    static QString _7k_plus() { return "\ue972"; }
    static QString _7mp() { return "\ue973"; }
    static QString _8k() { return "\ue974"; }
    static QString _8k_plus() { return "\ue975"; }
    static QString _8mp() { return "\ue976"; }
    static QString _9k() { return "\ue977"; }
    static QString _9k_plus() { return "\ue978"; }
    static QString _9mp() { return "\ue979"; }
    static QString _class() { return "\ue86e"; }
    static QString _delete() { return "\ue872"; }
    static QString _explicit() { return "\ue01e"; }
    static QString _public() { return "\ue80b"; }
    static QString ac_unit() { return "\ueb3b"; }
    static QString access_alarm() { return "\ue190"; }
    static QString access_alarms() { return "\ue191"; }
    static QString access_time() { return "\ue192"; }
    static QString accessibility() { return "\ue84e"; }
    static QString accessibility_new() { return "\ue92c"; }
    static QString accessible() { return "\ue914"; }
    static QString accessible_forward() { return "\ue934"; }
    static QString account_balance() { return "\ue84f"; }
    static QString account_balance_wallet() { return "\ue850"; }
    static QString account_box() { return "\ue851"; }
    static QString account_circle() { return "\ue853"; }
    static QString account_tree() { return "\ue97a"; }
    static QString adb() { return "\ue60e"; }
    static QString add() { return "\ue145"; }
    static QString add_a_photo() { return "\ue439"; }
    static QString add_alarm() { return "\ue193"; }
    static QString add_alert() { return "\ue003"; }
    static QString add_box() { return "\ue146"; }
    static QString add_call() { return "\ue0e8"; }
    static QString add_chart() { return "\ue97b"; }
    static QString add_circle() { return "\ue147"; }
    static QString add_circle_outline() { return "\ue148"; }
    static QString add_comment() { return "\ue266"; }
    static QString add_ic_call() { return "\ue97c"; }
    static QString add_link() { return "\ue178"; }
    static QString add_location() { return "\ue567"; }
    static QString add_moderator() { return "\ue97d"; }
    static QString add_photo_alternate() { return "\ue43e"; }
    static QString add_shopping_cart() { return "\ue854"; }
    static QString add_to_home_screen() { return "\ue1fe"; }
    static QString add_to_photos() { return "\ue39d"; }
    static QString add_to_queue() { return "\ue05c"; }
    static QString adjust() { return "\ue39e"; }
    static QString airline_seat_flat() { return "\ue630"; }
    static QString airline_seat_flat_angled() { return "\ue631"; }
    static QString airline_seat_individual_suite() { return "\ue632"; }
    static QString airline_seat_legroom_extra() { return "\ue633"; }
    static QString airline_seat_legroom_normal() { return "\ue634"; }
    static QString airline_seat_legroom_reduced() { return "\ue635"; }
    static QString airline_seat_recline_extra() { return "\ue636"; }
    static QString airline_seat_recline_normal() { return "\ue637"; }
    static QString airplanemode_active() { return "\ue195"; }
    static QString airplanemode_inactive() { return "\ue194"; }
    static QString airplanemode_off() { return "\ue194"; }
    static QString airplanemode_on() { return "\ue195"; }
    static QString airplay() { return "\ue055"; }
    static QString airport_shuttle() { return "\ueb3c"; }
    static QString alarm() { return "\ue855"; }
    static QString alarm_add() { return "\ue856"; }
    static QString alarm_off() { return "\ue857"; }
    static QString alarm_on() { return "\ue858"; }
    static QString album() { return "\ue019"; }
    static QString all_inbox() { return "\ue97f"; }
    static QString all_inclusive() { return "\ueb3d"; }
    static QString all_out() { return "\ue90b"; }
    static QString alternate_email() { return "\ue0e6"; }
    static QString amp_stories() { return "\uea13"; }
    static QString android() { return "\ue859"; }
    static QString announcement() { return "\ue85a"; }
    static QString apartment() { return "\uea40"; }
    static QString approval() { return "\ue982"; }
    static QString apps() { return "\ue5c3"; }
    static QString archive() { return "\ue149"; }
    static QString arrow_back() { return "\ue5c4"; }
    static QString arrow_back_ios() { return "\ue5e0"; }
    static QString arrow_downward() { return "\ue5db"; }
    static QString arrow_drop_down() { return "\ue5c5"; }
    static QString arrow_drop_down_circle() { return "\ue5c6"; }
    static QString arrow_drop_up() { return "\ue5c7"; }
    static QString arrow_forward() { return "\ue5c8"; }
    static QString arrow_forward_ios() { return "\ue5e1"; }
    static QString arrow_left() { return "\ue5de"; }
    static QString arrow_right() { return "\ue5df"; }
    static QString arrow_right_alt() { return "\ue941"; }
    static QString arrow_upward() { return "\ue5d8"; }
    static QString art_track() { return "\ue060"; }
    static QString aspect_ratio() { return "\ue85b"; }
    static QString assessment() { return "\ue85c"; }
    static QString assignment() { return "\ue85d"; }
    static QString assignment_ind() { return "\ue85e"; }
    static QString assignment_late() { return "\ue85f"; }
    static QString assignment_return() { return "\ue860"; }
    static QString assignment_returned() { return "\ue861"; }
    static QString assignment_turned_in() { return "\ue862"; }
    static QString assistant() { return "\ue39f"; }
    static QString assistant_direction() { return "\ue988"; }
    static QString assistant_navigation() { return "\ue989"; }
    static QString assistant_photo() { return "\ue3a0"; }
    static QString atm() { return "\ue573"; }
    static QString attach_file() { return "\ue226"; }
    static QString attach_money() { return "\ue227"; }
    static QString attachment() { return "\ue2bc"; }
    static QString attractions() { return "\uea52"; }
    static QString audiotrack() { return "\ue3a1"; }
    static QString autorenew() { return "\ue863"; }
    static QString av_timer() { return "\ue01b"; }
    static QString backspace() { return "\ue14a"; }
    static QString backup() { return "\ue864"; }
    static QString badge() { return "\uea67"; }
    static QString bakery_dining() { return "\uea53"; }
    static QString ballot() { return "\ue172"; }
    static QString bar_chart() { return "\ue26b"; }
    static QString bathtub() { return "\uea41"; }
    static QString battery_alert() { return "\ue19c"; }
    static QString battery_charging_full() { return "\ue1a3"; }
    static QString battery_full() { return "\ue1a4"; }
    static QString battery_std() { return "\ue1a5"; }
    static QString battery_unknown() { return "\ue1a6"; }
    static QString beach_access() { return "\ueb3e"; }
    static QString beenhere() { return "\ue52d"; }
    static QString block() { return "\ue14b"; }
    static QString bluetooth() { return "\ue1a7"; }
    static QString bluetooth_audio() { return "\ue60f"; }
    static QString bluetooth_connected() { return "\ue1a8"; }
    static QString bluetooth_disabled() { return "\ue1a9"; }
    static QString bluetooth_searching() { return "\ue1aa"; }
    static QString blur_circular() { return "\ue3a2"; }
    static QString blur_linear() { return "\ue3a3"; }
    static QString blur_off() { return "\ue3a4"; }
    static QString blur_on() { return "\ue3a5"; }
    static QString bolt() { return "\uea0b"; }
    static QString book() { return "\ue865"; }
    static QString bookmark() { return "\ue866"; }
    static QString bookmark_border() { return "\ue867"; }
    static QString bookmark_outline() { return "\ue867"; }
    static QString bookmarks() { return "\ue98b"; }
    static QString border_all() { return "\ue228"; }
    static QString border_bottom() { return "\ue229"; }
    static QString border_clear() { return "\ue22a"; }
    static QString border_color() { return "\ue22b"; }
    static QString border_horizontal() { return "\ue22c"; }
    static QString border_inner() { return "\ue22d"; }
    static QString border_left() { return "\ue22e"; }
    static QString border_outer() { return "\ue22f"; }
    static QString border_right() { return "\ue230"; }
    static QString border_style() { return "\ue231"; }
    static QString border_top() { return "\ue232"; }
    static QString border_vertical() { return "\ue233"; }
    static QString branding_watermark() { return "\ue06b"; }
    static QString breakfast_dining() { return "\uea54"; }
    static QString brightness_1() { return "\ue3a6"; }
    static QString brightness_2() { return "\ue3a7"; }
    static QString brightness_3() { return "\ue3a8"; }
    static QString brightness_4() { return "\ue3a9"; }
    static QString brightness_5() { return "\ue3aa"; }
    static QString brightness_6() { return "\ue3ab"; }
    static QString brightness_7() { return "\ue3ac"; }
    static QString brightness_auto() { return "\ue1ab"; }
    static QString brightness_high() { return "\ue1ac"; }
    static QString brightness_low() { return "\ue1ad"; }
    static QString brightness_medium() { return "\ue1ae"; }
    static QString broken_image() { return "\ue3ad"; }
    static QString brunch_dining() { return "\uea73"; }
    static QString brush() { return "\ue3ae"; }
    static QString bubble_chart() { return "\ue6dd"; }
    static QString bug_report() { return "\ue868"; }
    static QString build() { return "\ue869"; }
    static QString burst_mode() { return "\ue43c"; }
    static QString bus_alert() { return "\ue98f"; }
    static QString business() { return "\ue0af"; }
    static QString business_center() { return "\ueb3f"; }
    static QString cached() { return "\ue86a"; }
    static QString cake() { return "\ue7e9"; }
    static QString calendar_today() { return "\ue935"; }
    static QString calendar_view_day() { return "\ue936"; }
    static QString call() { return "\ue0b0"; }
    static QString call_end() { return "\ue0b1"; }
    static QString call_made() { return "\ue0b2"; }
    static QString call_merge() { return "\ue0b3"; }
    static QString call_missed() { return "\ue0b4"; }
    static QString call_missed_outgoing() { return "\ue0e4"; }
    static QString call_received() { return "\ue0b5"; }
    static QString call_split() { return "\ue0b6"; }
    static QString call_to_action() { return "\ue06c"; }
    static QString camera() { return "\ue3af"; }
    static QString camera_alt() { return "\ue3b0"; }
    static QString camera_enhance() { return "\ue8fc"; }
    static QString camera_front() { return "\ue3b1"; }
    static QString camera_rear() { return "\ue3b2"; }
    static QString camera_roll() { return "\ue3b3"; }
    static QString cancel() { return "\ue5c9"; }
    static QString cancel_presentation() { return "\ue0e9"; }
    static QString cancel_schedule_send() { return "\uea39"; }
    static QString car_rental() { return "\uea55"; }
    static QString car_repair() { return "\uea56"; }
    static QString card_giftcard() { return "\ue8f6"; }
    static QString card_membership() { return "\ue8f7"; }
    static QString card_travel() { return "\ue8f8"; }
    static QString cases() { return "\ue992"; }
    static QString casino() { return "\ueb40"; }
    static QString cast() { return "\ue307"; }
    static QString cast_connected() { return "\ue308"; }
    static QString category() { return "\ue574"; }
    static QString celebration() { return "\uea65"; }
    static QString cell_wifi() { return "\ue0ec"; }
    static QString center_focus_strong() { return "\ue3b4"; }
    static QString center_focus_weak() { return "\ue3b5"; }
    static QString change_history() { return "\ue86b"; }
    static QString chat() { return "\ue0b7"; }
    static QString chat_bubble() { return "\ue0ca"; }
    static QString chat_bubble_outline() { return "\ue0cb"; }
    static QString check() { return "\ue5ca"; }
    static QString check_box() { return "\ue834"; }
    static QString check_box_outline_blank() { return "\ue835"; }
    static QString check_circle() { return "\ue86c"; }
    static QString check_circle_outline() { return "\ue92d"; }
    static QString chevron_left() { return "\ue5cb"; }
    static QString chevron_right() { return "\ue5cc"; }
    static QString child_care() { return "\ueb41"; }
    static QString child_friendly() { return "\ueb42"; }
    static QString chrome_reader_mode() { return "\ue86d"; }
    static QString circle_notifications() { return "\ue994"; }
    static QString clear() { return "\ue14c"; }
    static QString clear_all() { return "\ue0b8"; }
    static QString close() { return "\ue5cd"; }
    static QString closed_caption() { return "\ue01c"; }
    static QString closed_caption_off() { return "\ue996"; }
    static QString cloud() { return "\ue2bd"; }
    static QString cloud_circle() { return "\ue2be"; }
    static QString cloud_done() { return "\ue2bf"; }
    static QString cloud_download() { return "\ue2c0"; }
    static QString cloud_off() { return "\ue2c1"; }
    static QString cloud_queue() { return "\ue2c2"; }
    static QString cloud_upload() { return "\ue2c3"; }
    static QString code() { return "\ue86f"; }
    static QString collections() { return "\ue3b6"; }
    static QString collections_bookmark() { return "\ue431"; }
    static QString color_lens() { return "\ue3b7"; }
    static QString colorize() { return "\ue3b8"; }
    static QString comment() { return "\ue0b9"; }
    static QString commute() { return "\ue940"; }
    static QString compare() { return "\ue3b9"; }
    static QString compare_arrows() { return "\ue915"; }
    static QString compass_calibration() { return "\ue57c"; }
    static QString compress() { return "\ue94d"; }
    static QString computer() { return "\ue30a"; }
    static QString confirmation_num() { return "\ue638"; }
    static QString confirmation_number() { return "\ue638"; }
    static QString connected_tv() { return "\ue998"; }
    static QString contact_mail() { return "\ue0d0"; }
    static QString contact_phone() { return "\ue0cf"; }
    static QString contact_support() { return "\ue94c"; }
    static QString contactless() { return "\uea71"; }
    static QString contacts() { return "\ue0ba"; }
    static QString content_copy() { return "\ue14d"; }
    static QString content_cut() { return "\ue14e"; }
    static QString content_paste() { return "\ue14f"; }
    static QString control_camera() { return "\ue074"; }
    static QString control_point() { return "\ue3ba"; }
    static QString control_point_duplicate() { return "\ue3bb"; }
    static QString copyright() { return "\ue90c"; }
    static QString create() { return "\ue150"; }
    static QString create_new_folder() { return "\ue2cc"; }
    static QString credit_card() { return "\ue870"; }
    static QString crop() { return "\ue3be"; }
    static QString crop_16_9() { return "\ue3bc"; }
    static QString crop_3_2() { return "\ue3bd"; }
    static QString crop_5_4() { return "\ue3bf"; }
    static QString crop_7_5() { return "\ue3c0"; }
    static QString crop_din() { return "\ue3c1"; }
    static QString crop_free() { return "\ue3c2"; }
    static QString crop_landscape() { return "\ue3c3"; }
    static QString crop_original() { return "\ue3c4"; }
    static QString crop_portrait() { return "\ue3c5"; }
    static QString crop_rotate() { return "\ue437"; }
    static QString crop_square() { return "\ue3c6"; }
    static QString dangerous() { return "\ue99a"; }
    static QString dashboard() { return "\ue871"; }
    static QString dashboard_customize() { return "\ue99b"; }
    static QString data_usage() { return "\ue1af"; }
    static QString date_range() { return "\ue916"; }
    static QString deck() { return "\uea42"; }
    static QString dehaze() { return "\ue3c7"; }
    static QString delete_forever() { return "\ue92b"; }
    static QString delete_outline() { return "\ue92e"; }
    static QString delete_sweep() { return "\ue16c"; }
    static QString delivery_dining() { return "\uea72"; }
    static QString departure_board() { return "\ue576"; }
    static QString description() { return "\ue873"; }
    static QString desktop_access_disabled() { return "\ue99d"; }
    static QString desktop_mac() { return "\ue30b"; }
    static QString desktop_windows() { return "\ue30c"; }
    static QString details() { return "\ue3c8"; }
    static QString developer_board() { return "\ue30d"; }
    static QString developer_mode() { return "\ue1b0"; }
    static QString device_hub() { return "\ue335"; }
    static QString device_thermostat() { return "\ue1ff"; }
    static QString device_unknown() { return "\ue339"; }
    static QString devices() { return "\ue1b1"; }
    static QString devices_other() { return "\ue337"; }
    static QString dialer_sip() { return "\ue0bb"; }
    static QString dialpad() { return "\ue0bc"; }
    static QString dinner_dining() { return "\uea57"; }
    static QString directions() { return "\ue52e"; }
    static QString directions_bike() { return "\ue52f"; }
    static QString directions_boat() { return "\ue532"; }
    static QString directions_bus() { return "\ue530"; }
    static QString directions_car() { return "\ue531"; }
    static QString directions_ferry() { return "\ue532"; }
    static QString directions_railway() { return "\ue534"; }
    static QString directions_run() { return "\ue566"; }
    static QString directions_subway() { return "\ue533"; }
    static QString directions_train() { return "\ue534"; }
    static QString directions_transit() { return "\ue535"; }
    static QString directions_walk() { return "\ue536"; }
    static QString disc_full() { return "\ue610"; }
    static QString dnd_forwardslash() { return "\ue611"; }
    static QString dns() { return "\ue875"; }
    static QString do_not_disturb() { return "\ue612"; }
    static QString do_not_disturb_alt() { return "\ue611"; }
    static QString do_not_disturb_off() { return "\ue643"; }
    static QString do_not_disturb_on() { return "\ue644"; }
    static QString dock() { return "\ue30e"; }
    static QString domain() { return "\ue7ee"; }
    static QString domain_disabled() { return "\ue0ef"; }
    static QString done() { return "\ue876"; }
    static QString done_all() { return "\ue877"; }
    static QString done_outline() { return "\ue92f"; }
    static QString donut_large() { return "\ue917"; }
    static QString donut_small() { return "\ue918"; }
    static QString double_arrow() { return "\uea50"; }
    static QString drafts() { return "\ue151"; }
    static QString drag_handle() { return "\ue25d"; }
    static QString drag_indicator() { return "\ue945"; }
    static QString drive_eta() { return "\ue613"; }
    static QString drive_file_move_outline() { return "\ue9a1"; }
    static QString drive_file_rename_outline() { return "\ue9a2"; }
    static QString drive_folder_upload() { return "\ue9a3"; }
    static QString dry_cleaning() { return "\uea58"; }
    static QString duo() { return "\ue9a5"; }
    static QString dvr() { return "\ue1b2"; }
    static QString dynamic_feed() { return "\uea14"; }
    static QString eco() { return "\uea35"; }
    static QString edit() { return "\ue3c9"; }
    static QString edit_attributes() { return "\ue578"; }
    static QString edit_location() { return "\ue568"; }
    static QString edit_off() { return "\ue950"; }
    static QString eject() { return "\ue8fb"; }
    static QString email() { return "\ue0be"; }
    static QString emoji_emotions() { return "\uea22"; }
    static QString emoji_events() { return "\uea23"; }
    static QString emoji_flags() { return "\uea1a"; }
    static QString emoji_food_beverage() { return "\uea1b"; }
    static QString emoji_nature() { return "\uea1c"; }
    static QString emoji_objects() { return "\uea24"; }
    static QString emoji_people() { return "\uea1d"; }
    static QString emoji_symbols() { return "\uea1e"; }
    static QString emoji_transportation() { return "\uea1f"; }
    static QString enhance_photo_translate() { return "\ue8fc"; }
    static QString enhanced_encryption() { return "\ue63f"; }
    static QString equalizer() { return "\ue01d"; }
    static QString error() { return "\ue000"; }
    static QString error_outline() { return "\ue001"; }
    static QString euro() { return "\uea15"; }
    static QString euro_symbol() { return "\ue926"; }
    static QString ev_station() { return "\ue56d"; }
    static QString event() { return "\ue878"; }
    static QString event_available() { return "\ue614"; }
    static QString event_busy() { return "\ue615"; }
    static QString event_note() { return "\ue616"; }
    static QString event_seat() { return "\ue903"; }
    static QString exit_to_app() { return "\ue879"; }
    static QString expand() { return "\ue94f"; }
    static QString expand_less() { return "\ue5ce"; }
    static QString expand_more() { return "\ue5cf"; }
    static QString explore() { return "\ue87a"; }
    static QString explore_off() { return "\ue9a8"; }
    static QString exposure() { return "\ue3ca"; }
    static QString exposure_minus_1() { return "\ue3cb"; }
    static QString exposure_minus_2() { return "\ue3cc"; }
    static QString exposure_neg_1() { return "\ue3cb"; }
    static QString exposure_neg_2() { return "\ue3cc"; }
    static QString exposure_plus_1() { return "\ue3cd"; }
    static QString exposure_plus_2() { return "\ue3ce"; }
    static QString exposure_zero() { return "\ue3cf"; }
    static QString extension() { return "\ue87b"; }
    static QString face() { return "\ue87c"; }
    static QString fast_forward() { return "\ue01f"; }
    static QString fast_rewind() { return "\ue020"; }
    static QString fastfood() { return "\ue57a"; }
    static QString favorite() { return "\ue87d"; }
    static QString favorite_border() { return "\ue87e"; }
    static QString favorite_outline() { return "\ue87e"; }
    static QString featured_play_list() { return "\ue06d"; }
    static QString featured_video() { return "\ue06e"; }
    static QString feedback() { return "\ue87f"; }
    static QString festival() { return "\uea68"; }
    static QString fiber_dvr() { return "\ue05d"; }
    static QString fiber_manual_record() { return "\ue061"; }
    static QString fiber_new() { return "\ue05e"; }
    static QString fiber_pin() { return "\ue06a"; }
    static QString fiber_smart_record() { return "\ue062"; }
    static QString file_copy() { return "\ue173"; }
    static QString file_download() { return "\ue2c4"; }
    static QString file_download_done() { return "\ue9aa"; }
    static QString file_present() { return "\uea0e"; }
    static QString file_upload() { return "\ue2c6"; }
    static QString filter() { return "\ue3d3"; }
    static QString filter_1() { return "\ue3d0"; }
    static QString filter_2() { return "\ue3d1"; }
    static QString filter_3() { return "\ue3d2"; }
    static QString filter_4() { return "\ue3d4"; }
    static QString filter_5() { return "\ue3d5"; }
    static QString filter_6() { return "\ue3d6"; }
    static QString filter_7() { return "\ue3d7"; }
    static QString filter_8() { return "\ue3d8"; }
    static QString filter_9() { return "\ue3d9"; }
    static QString filter_9_plus() { return "\ue3da"; }
    static QString filter_b_and_w() { return "\ue3db"; }
    static QString filter_center_focus() { return "\ue3dc"; }
    static QString filter_drama() { return "\ue3dd"; }
    static QString filter_frames() { return "\ue3de"; }
    static QString filter_hdr() { return "\ue3df"; }
    static QString filter_list() { return "\ue152"; }
    static QString filter_list_alt() { return "\ue94e"; }
    static QString filter_none() { return "\ue3e0"; }
    static QString filter_tilt_shift() { return "\ue3e2"; }
    static QString filter_vintage() { return "\ue3e3"; }
    static QString find_in_page() { return "\ue880"; }
    static QString find_replace() { return "\ue881"; }
    static QString fingerprint() { return "\ue90d"; }
    static QString fireplace() { return "\uea43"; }
    static QString first_page() { return "\ue5dc"; }
    static QString fit_screen() { return "\uea10"; }
    static QString fitness_center() { return "\ueb43"; }
    static QString flag() { return "\ue153"; }
    static QString flare() { return "\ue3e4"; }
    static QString flash_auto() { return "\ue3e5"; }
    static QString flash_off() { return "\ue3e6"; }
    static QString flash_on() { return "\ue3e7"; }
    static QString flight() { return "\ue539"; }
    static QString flight_land() { return "\ue904"; }
    static QString flight_takeoff() { return "\ue905"; }
    static QString flip() { return "\ue3e8"; }
    static QString flip_camera_android() { return "\uea37"; }
    static QString flip_camera_ios() { return "\uea38"; }
    static QString flip_to_back() { return "\ue882"; }
    static QString flip_to_front() { return "\ue883"; }
    static QString folder() { return "\ue2c7"; }
    static QString folder_open() { return "\ue2c8"; }
    static QString folder_shared() { return "\ue2c9"; }
    static QString folder_special() { return "\ue617"; }
    static QString font_download() { return "\ue167"; }
    static QString format_align_center() { return "\ue234"; }
    static QString format_align_justify() { return "\ue235"; }
    static QString format_align_left() { return "\ue236"; }
    static QString format_align_right() { return "\ue237"; }
    static QString format_bold() { return "\ue238"; }
    static QString format_clear() { return "\ue239"; }
    static QString format_color_fill() { return "\ue23a"; }
    static QString format_color_reset() { return "\ue23b"; }
    static QString format_color_text() { return "\ue23c"; }
    static QString format_indent_decrease() { return "\ue23d"; }
    static QString format_indent_increase() { return "\ue23e"; }
    static QString format_italic() { return "\ue23f"; }
    static QString format_line_spacing() { return "\ue240"; }
    static QString format_list_bulleted() { return "\ue241"; }
    static QString format_list_numbered() { return "\ue242"; }
    static QString format_list_numbered_rtl() { return "\ue267"; }
    static QString format_paint() { return "\ue243"; }
    static QString format_quote() { return "\ue244"; }
    static QString format_shapes() { return "\ue25e"; }
    static QString format_size() { return "\ue245"; }
    static QString format_strikethrough() { return "\ue246"; }
    static QString format_textdirection_l_to_r() { return "\ue247"; }
    static QString format_textdirection_r_to_l() { return "\ue248"; }
    static QString format_underline() { return "\ue249"; }
    static QString format_underlined() { return "\ue249"; }
    static QString forum() { return "\ue0bf"; }
    static QString forward() { return "\ue154"; }
    static QString forward_10() { return "\ue056"; }
    static QString forward_30() { return "\ue057"; }
    static QString forward_5() { return "\ue058"; }
    static QString free_breakfast() { return "\ueb44"; }
    static QString fullscreen() { return "\ue5d0"; }
    static QString fullscreen_exit() { return "\ue5d1"; }
    static QString functions() { return "\ue24a"; }
    static QString g_translate() { return "\ue927"; }
    static QString gamepad() { return "\ue30f"; }
    static QString games() { return "\ue021"; }
    static QString gavel() { return "\ue90e"; }
    static QString gesture() { return "\ue155"; }
    static QString get_app() { return "\ue884"; }
    static QString gif() { return "\ue908"; }
    static QString goat() { return "\uebff"; }
    static QString golf_course() { return "\ueb45"; }
    static QString gps_fixed() { return "\ue1b3"; }
    static QString gps_not_fixed() { return "\ue1b4"; }
    static QString gps_off() { return "\ue1b5"; }
    static QString grade() { return "\ue885"; }
    static QString gradient() { return "\ue3e9"; }
    static QString grain() { return "\ue3ea"; }
    static QString graphic_eq() { return "\ue1b8"; }
    static QString grid_off() { return "\ue3eb"; }
    static QString grid_on() { return "\ue3ec"; }
    static QString grid_view() { return "\ue9b0"; }
    static QString group() { return "\ue7ef"; }
    static QString group_add() { return "\ue7f0"; }
    static QString group_work() { return "\ue886"; }
    static QString hail() { return "\ue9b1"; }
    static QString hardware() { return "\uea59"; }
    static QString hd() { return "\ue052"; }
    static QString hdr_off() { return "\ue3ed"; }
    static QString hdr_on() { return "\ue3ee"; }
    static QString hdr_strong() { return "\ue3f1"; }
    static QString hdr_weak() { return "\ue3f2"; }
    static QString headset() { return "\ue310"; }
    static QString headset_mic() { return "\ue311"; }
    static QString headset_off() { return "\ue33a"; }
    static QString healing() { return "\ue3f3"; }
    static QString hearing() { return "\ue023"; }
    static QString height() { return "\uea16"; }
    static QString help() { return "\ue887"; }
    static QString help_outline() { return "\ue8fd"; }
    static QString high_quality() { return "\ue024"; }
    static QString highlight() { return "\ue25f"; }
    static QString highlight_off() { return "\ue888"; }
    static QString highlight_remove() { return "\ue888"; }
    static QString history() { return "\ue889"; }
    static QString home() { return "\ue88a"; }
    static QString home_filled() { return "\ue9b2"; }
    static QString home_work() { return "\uea09"; }
    static QString horizontal_split() { return "\ue947"; }
    static QString hot_tub() { return "\ueb46"; }
    static QString hotel() { return "\ue53a"; }
    static QString hourglass_empty() { return "\ue88b"; }
    static QString hourglass_full() { return "\ue88c"; }
    static QString house() { return "\uea44"; }
    static QString how_to_reg() { return "\ue174"; }
    static QString how_to_vote() { return "\ue175"; }
    static QString http() { return "\ue902"; }
    static QString https() { return "\ue88d"; }
    static QString icecream() { return "\uea69"; }
    static QString image() { return "\ue3f4"; }
    static QString image_aspect_ratio() { return "\ue3f5"; }
    static QString image_search() { return "\ue43f"; }
    static QString imagesearch_roller() { return "\ue9b4"; }
    static QString import_contacts() { return "\ue0e0"; }
    static QString import_export() { return "\ue0c3"; }
    static QString important_devices() { return "\ue912"; }
    static QString inbox() { return "\ue156"; }
    static QString indeterminate_check_box() { return "\ue909"; }
    static QString info() { return "\ue88e"; }
    static QString info_outline() { return "\ue88f"; }
    static QString input() { return "\ue890"; }
    static QString insert_chart() { return "\ue24b"; }
    static QString insert_chart_outlined() { return "\ue26a"; }
    static QString insert_comment() { return "\ue24c"; }
    static QString insert_drive_file() { return "\ue24d"; }
    static QString insert_emoticon() { return "\ue24e"; }
    static QString insert_invitation() { return "\ue24f"; }
    static QString insert_link() { return "\ue250"; }
    static QString insert_photo() { return "\ue251"; }
    static QString inventory() { return "\ue179"; }
    static QString invert_colors() { return "\ue891"; }
    static QString invert_colors_off() { return "\ue0c4"; }
    static QString invert_colors_on() { return "\ue891"; }
    static QString iso() { return "\ue3f6"; }
    static QString keyboard() { return "\ue312"; }
    static QString keyboard_arrow_down() { return "\ue313"; }
    static QString keyboard_arrow_left() { return "\ue314"; }
    static QString keyboard_arrow_right() { return "\ue315"; }
    static QString keyboard_arrow_up() { return "\ue316"; }
    static QString keyboard_backspace() { return "\ue317"; }
    static QString keyboard_capslock() { return "\ue318"; }
    static QString keyboard_control() { return "\ue5d3"; }
    static QString keyboard_hide() { return "\ue31a"; }
    static QString keyboard_return() { return "\ue31b"; }
    static QString keyboard_tab() { return "\ue31c"; }
    static QString keyboard_voice() { return "\ue31d"; }
    static QString king_bed() { return "\uea45"; }
    static QString kitchen() { return "\ueb47"; }
    static QString label() { return "\ue892"; }
    static QString label_important() { return "\ue937"; }
    static QString label_important_outline() { return "\ue948"; }
    static QString label_off() { return "\ue9b6"; }
    static QString label_outline() { return "\ue893"; }
    static QString landscape() { return "\ue3f7"; }
    static QString language() { return "\ue894"; }
    static QString laptop() { return "\ue31e"; }
    static QString laptop_chromebook() { return "\ue31f"; }
    static QString laptop_mac() { return "\ue320"; }
    static QString laptop_windows() { return "\ue321"; }
    static QString last_page() { return "\ue5dd"; }
    static QString launch() { return "\ue895"; }
    static QString layers() { return "\ue53b"; }
    static QString layers_clear() { return "\ue53c"; }
    static QString leak_add() { return "\ue3f8"; }
    static QString leak_remove() { return "\ue3f9"; }
    static QString lens() { return "\ue3fa"; }
    static QString library_add() { return "\ue02e"; }
    static QString library_add_check() { return "\ue9b7"; }
    static QString library_books() { return "\ue02f"; }
    static QString library_music() { return "\ue030"; }
    static QString lightbulb() { return "\ue0f0"; }
    static QString lightbulb_outline() { return "\ue90f"; }
    static QString line_style() { return "\ue919"; }
    static QString line_weight() { return "\ue91a"; }
    static QString linear_scale() { return "\ue260"; }
    static QString link() { return "\ue157"; }
    static QString link_off() { return "\ue16f"; }
    static QString linked_camera() { return "\ue438"; }
    static QString liquor() { return "\uea60"; }
    static QString list() { return "\ue896"; }
    static QString list_alt() { return "\ue0ee"; }
    static QString live_help() { return "\ue0c6"; }
    static QString live_tv() { return "\ue639"; }
    static QString local_activity() { return "\ue53f"; }
    static QString local_airport() { return "\ue53d"; }
    static QString local_atm() { return "\ue53e"; }
    static QString local_attraction() { return "\ue53f"; }
    static QString local_bar() { return "\ue540"; }
    static QString local_cafe() { return "\ue541"; }
    static QString local_car_wash() { return "\ue542"; }
    static QString local_convenience_store() { return "\ue543"; }
    static QString local_dining() { return "\ue556"; }
    static QString local_drink() { return "\ue544"; }
    static QString local_florist() { return "\ue545"; }
    static QString local_gas_station() { return "\ue546"; }
    static QString local_grocery_store() { return "\ue547"; }
    static QString local_hospital() { return "\ue548"; }
    static QString local_hotel() { return "\ue549"; }
    static QString local_laundry_service() { return "\ue54a"; }
    static QString local_library() { return "\ue54b"; }
    static QString local_mall() { return "\ue54c"; }
    static QString local_movies() { return "\ue54d"; }
    static QString local_offer() { return "\ue54e"; }
    static QString local_parking() { return "\ue54f"; }
    static QString local_pharmacy() { return "\ue550"; }
    static QString local_phone() { return "\ue551"; }
    static QString local_pizza() { return "\ue552"; }
    static QString local_play() { return "\ue553"; }
    static QString local_post_office() { return "\ue554"; }
    static QString local_print_shop() { return "\ue555"; }
    static QString local_printshop() { return "\ue555"; }
    static QString local_restaurant() { return "\ue556"; }
    static QString local_see() { return "\ue557"; }
    static QString local_shipping() { return "\ue558"; }
    static QString local_taxi() { return "\ue559"; }
    static QString location_city() { return "\ue7f1"; }
    static QString location_disabled() { return "\ue1b6"; }
    static QString location_history() { return "\ue55a"; }
    static QString location_off() { return "\ue0c7"; }
    static QString location_on() { return "\ue0c8"; }
    static QString location_searching() { return "\ue1b7"; }
    static QString lock() { return "\ue897"; }
    static QString lock_open() { return "\ue898"; }
    static QString lock_outline() { return "\ue899"; }
    static QString logout() { return "\ue9ba"; }
    static QString looks() { return "\ue3fc"; }
    static QString looks_3() { return "\ue3fb"; }
    static QString looks_4() { return "\ue3fd"; }
    static QString looks_5() { return "\ue3fe"; }
    static QString looks_6() { return "\ue3ff"; }
    static QString looks_one() { return "\ue400"; }
    static QString looks_two() { return "\ue401"; }
    static QString loop() { return "\ue028"; }
    static QString loupe() { return "\ue402"; }
    static QString low_priority() { return "\ue16d"; }
    static QString loyalty() { return "\ue89a"; }
    static QString lunch_dining() { return "\uea61"; }
    static QString mail() { return "\ue158"; }
    static QString mail_outline() { return "\ue0e1"; }
    static QString map() { return "\ue55b"; }
    static QString margin() { return "\ue9bb"; }
    static QString mark_as_unread() { return "\ue9bc"; }
    static QString markunread() { return "\ue159"; }
    static QString markunread_mailbox() { return "\ue89b"; }
    static QString maximize() { return "\ue930"; }
    static QString meeting_room() { return "\ueb4f"; }
    static QString memory() { return "\ue322"; }
    static QString menu() { return "\ue5d2"; }
    static QString menu_book() { return "\uea19"; }
    static QString menu_open() { return "\ue9bd"; }
    static QString merge_type() { return "\ue252"; }
    static QString message() { return "\ue0c9"; }
    static QString messenger() { return "\ue0ca"; }
    static QString messenger_outline() { return "\ue0cb"; }
    static QString mic() { return "\ue029"; }
    static QString mic_none() { return "\ue02a"; }
    static QString mic_off() { return "\ue02b"; }
    static QString minimize() { return "\ue931"; }
    static QString missed_video_call() { return "\ue073"; }
    static QString mms() { return "\ue618"; }
    static QString mobile_friendly() { return "\ue200"; }
    static QString mobile_off() { return "\ue201"; }
    static QString mobile_screen_share() { return "\ue0e7"; }
    static QString mode_comment() { return "\ue253"; }
    static QString mode_edit() { return "\ue254"; }
    static QString monetization_on() { return "\ue263"; }
    static QString money() { return "\ue57d"; }
    static QString money_off() { return "\ue25c"; }
    static QString monochrome_photos() { return "\ue403"; }
    static QString mood() { return "\ue7f2"; }
    static QString mood_bad() { return "\ue7f3"; }
    static QString more() { return "\ue619"; }
    static QString more_horiz() { return "\ue5d3"; }
    static QString more_vert() { return "\ue5d4"; }
    static QString motorcycle() { return "\ue91b"; }
    static QString mouse() { return "\ue323"; }
    static QString move_to_inbox() { return "\ue168"; }
    static QString movie() { return "\ue02c"; }
    static QString movie_creation() { return "\ue404"; }
    static QString movie_filter() { return "\ue43a"; }
    static QString mp() { return "\ue9c3"; }
    static QString multiline_chart() { return "\ue6df"; }
    static QString multitrack_audio() { return "\ue1b8"; }
    static QString museum() { return "\uea36"; }
    static QString music_note() { return "\ue405"; }
    static QString music_off() { return "\ue440"; }
    static QString music_video() { return "\ue063"; }
    static QString my_library_add() { return "\ue02e"; }
    static QString my_library_books() { return "\ue02f"; }
    static QString my_library_music() { return "\ue030"; }
    static QString my_location() { return "\ue55c"; }
    static QString nature() { return "\ue406"; }
    static QString nature_people() { return "\ue407"; }
    static QString navigate_before() { return "\ue408"; }
    static QString navigate_next() { return "\ue409"; }
    static QString navigation() { return "\ue55d"; }
    static QString near_me() { return "\ue569"; }
    static QString network_cell() { return "\ue1b9"; }
    static QString network_check() { return "\ue640"; }
    static QString network_locked() { return "\ue61a"; }
    static QString network_wifi() { return "\ue1ba"; }
    static QString new_releases() { return "\ue031"; }
    static QString next_week() { return "\ue16a"; }
    static QString nfc() { return "\ue1bb"; }
    static QString nightlife() { return "\uea62"; }
    static QString nights_stay() { return "\uea46"; }
    static QString no_encryption() { return "\ue641"; }
    static QString no_meeting_room() { return "\ueb4e"; }
    static QString no_sim() { return "\ue0cc"; }
    static QString not_interested() { return "\ue033"; }
    static QString not_listed_location() { return "\ue575"; }
    static QString note() { return "\ue06f"; }
    static QString note_add() { return "\ue89c"; }
    static QString notes() { return "\ue26c"; }
    static QString notification_important() { return "\ue004"; }
    static QString notifications() { return "\ue7f4"; }
    static QString notifications_active() { return "\ue7f7"; }
    static QString notifications_none() { return "\ue7f5"; }
    static QString notifications_off() { return "\ue7f6"; }
    static QString notifications_on() { return "\ue7f7"; }
    static QString notifications_paused() { return "\ue7f8"; }
    static QString now_wallpaper() { return "\ue1bc"; }
    static QString now_widgets() { return "\ue1bd"; }
    static QString offline_bolt() { return "\ue932"; }
    static QString offline_pin() { return "\ue90a"; }
    static QString offline_share() { return "\ue9c5"; }
    static QString ondemand_video() { return "\ue63a"; }
    static QString opacity() { return "\ue91c"; }
    static QString open_in_browser() { return "\ue89d"; }
    static QString open_in_new() { return "\ue89e"; }
    static QString open_with() { return "\ue89f"; }
    static QString outdoor_grill() { return "\uea47"; }
    static QString outlined_flag() { return "\ue16e"; }
    static QString padding() { return "\ue9c8"; }
    static QString pages() { return "\ue7f9"; }
    static QString pageview() { return "\ue8a0"; }
    static QString palette() { return "\ue40a"; }
    static QString pan_tool() { return "\ue925"; }
    static QString panorama() { return "\ue40b"; }
    static QString panorama_fish_eye() { return "\ue40c"; }
    static QString panorama_fisheye() { return "\ue40c"; }
    static QString panorama_horizontal() { return "\ue40d"; }
    static QString panorama_photosphere() { return "\ue9c9"; }
    static QString panorama_photosphere_select() { return "\ue9ca"; }
    static QString panorama_vertical() { return "\ue40e"; }
    static QString panorama_wide_angle() { return "\ue40f"; }
    static QString park() { return "\uea63"; }
    static QString party_mode() { return "\ue7fa"; }
    static QString pause() { return "\ue034"; }
    static QString pause_circle_filled() { return "\ue035"; }
    static QString pause_circle_outline() { return "\ue036"; }
    static QString pause_presentation() { return "\ue0ea"; }
    static QString payment() { return "\ue8a1"; }
    static QString people() { return "\ue7fb"; }
    static QString people_alt() { return "\uea21"; }
    static QString people_outline() { return "\ue7fc"; }
    static QString perm_camera_mic() { return "\ue8a2"; }
    static QString perm_contact_cal() { return "\ue8a3"; }
    static QString perm_contact_calendar() { return "\ue8a3"; }
    static QString perm_data_setting() { return "\ue8a4"; }
    static QString perm_device_info() { return "\ue8a5"; }
    static QString perm_device_information() { return "\ue8a5"; }
    static QString perm_identity() { return "\ue8a6"; }
    static QString perm_media() { return "\ue8a7"; }
    static QString perm_phone_msg() { return "\ue8a8"; }
    static QString perm_scan_wifi() { return "\ue8a9"; }
    static QString person() { return "\ue7fd"; }
    static QString person_add() { return "\ue7fe"; }
    static QString person_add_disabled() { return "\ue9cb"; }
    static QString person_outline() { return "\ue7ff"; }
    static QString person_pin() { return "\ue55a"; }
    static QString person_pin_circle() { return "\ue56a"; }
    static QString personal_video() { return "\ue63b"; }
    static QString pets() { return "\ue91d"; }
    static QString phone() { return "\ue0cd"; }
    static QString phone_android() { return "\ue324"; }
    static QString phone_bluetooth_speaker() { return "\ue61b"; }
    static QString phone_callback() { return "\ue649"; }
    static QString phone_disabled() { return "\ue9cc"; }
    static QString phone_enabled() { return "\ue9cd"; }
    static QString phone_forwarded() { return "\ue61c"; }
    static QString phone_in_talk() { return "\ue61d"; }
    static QString phone_iphone() { return "\ue325"; }
    static QString phone_locked() { return "\ue61e"; }
    static QString phone_missed() { return "\ue61f"; }
    static QString phone_paused() { return "\ue620"; }
    static QString phonelink() { return "\ue326"; }
    static QString phonelink_erase() { return "\ue0db"; }
    static QString phonelink_lock() { return "\ue0dc"; }
    static QString phonelink_off() { return "\ue327"; }
    static QString phonelink_ring() { return "\ue0dd"; }
    static QString phonelink_setup() { return "\ue0de"; }
    static QString photo() { return "\ue410"; }
    static QString photo_album() { return "\ue411"; }
    static QString photo_camera() { return "\ue412"; }
    static QString photo_filter() { return "\ue43b"; }
    static QString photo_library() { return "\ue413"; }
    static QString photo_size_select_actual() { return "\ue432"; }
    static QString photo_size_select_large() { return "\ue433"; }
    static QString photo_size_select_small() { return "\ue434"; }
    static QString picture_as_pdf() { return "\ue415"; }
    static QString picture_in_picture() { return "\ue8aa"; }
    static QString picture_in_picture_alt() { return "\ue911"; }
    static QString pie_chart() { return "\ue6c4"; }
    static QString pie_chart_outlined() { return "\ue6c5"; }
    static QString pin_drop() { return "\ue55e"; }
    static QString pivot_table_chart() { return "\ue9ce"; }
    static QString place() { return "\ue55f"; }
    static QString play_arrow() { return "\ue037"; }
    static QString play_circle_fill() { return "\ue038"; }
    static QString play_circle_filled() { return "\ue038"; }
    static QString play_circle_outline() { return "\ue039"; }
    static QString play_for_work() { return "\ue906"; }
    static QString playlist_add() { return "\ue03b"; }
    static QString playlist_add_check() { return "\ue065"; }
    static QString playlist_play() { return "\ue05f"; }
    static QString plus_one() { return "\ue800"; }
    static QString policy() { return "\uea17"; }
    static QString poll() { return "\ue801"; }
    static QString polymer() { return "\ue8ab"; }
    static QString pool() { return "\ueb48"; }
    static QString portable_wifi_off() { return "\ue0ce"; }
    static QString portrait() { return "\ue416"; }
    static QString post_add() { return "\uea20"; }
    static QString power() { return "\ue63c"; }
    static QString power_input() { return "\ue336"; }
    static QString power_off() { return "\ue646"; }
    static QString power_settings_new() { return "\ue8ac"; }
    static QString pregnant_woman() { return "\ue91e"; }
    static QString present_to_all() { return "\ue0df"; }
    static QString print() { return "\ue8ad"; }
    static QString print_disabled() { return "\ue9cf"; }
    static QString priority_high() { return "\ue645"; }
    static QString publish() { return "\ue255"; }
    static QString query_builder() { return "\ue8ae"; }
    static QString question_answer() { return "\ue8af"; }
    static QString queue() { return "\ue03c"; }
    static QString queue_music() { return "\ue03d"; }
    static QString queue_play_next() { return "\ue066"; }
    static QString quick_contacts_dialer() { return "\ue0cf"; }
    static QString quick_contacts_mail() { return "\ue0d0"; }
    static QString radio() { return "\ue03e"; }
    static QString radio_button_checked() { return "\ue837"; }
    static QString radio_button_off() { return "\ue836"; }
    static QString radio_button_on() { return "\ue837"; }
    static QString radio_button_unchecked() { return "\ue836"; }
    static QString railway_alert() { return "\ue9d1"; }
    static QString ramen_dining() { return "\uea64"; }
    static QString rate_review() { return "\ue560"; }
    static QString receipt() { return "\ue8b0"; }
    static QString recent_actors() { return "\ue03f"; }
    static QString recommend() { return "\ue9d2"; }
    static QString record_voice_over() { return "\ue91f"; }
    static QString redeem() { return "\ue8b1"; }
    static QString redo() { return "\ue15a"; }
    static QString refresh() { return "\ue5d5"; }
    static QString remove() { return "\ue15b"; }
    static QString remove_circle() { return "\ue15c"; }
    static QString remove_circle_outline() { return "\ue15d"; }
    static QString remove_done() { return "\ue9d3"; }
    static QString remove_from_queue() { return "\ue067"; }
    static QString remove_moderator() { return "\ue9d4"; }
    static QString remove_red_eye() { return "\ue417"; }
    static QString remove_shopping_cart() { return "\ue928"; }
    static QString reorder() { return "\ue8fe"; }
    static QString repeat() { return "\ue040"; }
    static QString repeat_on() { return "\ue9d6"; }
    static QString repeat_one() { return "\ue041"; }
    static QString repeat_one_on() { return "\ue9d7"; }
    static QString replay() { return "\ue042"; }
    static QString replay_10() { return "\ue059"; }
    static QString replay_30() { return "\ue05a"; }
    static QString replay_5() { return "\ue05b"; }
    static QString replay_circle_filled() { return "\ue9d8"; }
    static QString reply() { return "\ue15e"; }
    static QString reply_all() { return "\ue15f"; }
    static QString report() { return "\ue160"; }
    static QString report_off() { return "\ue170"; }
    static QString report_problem() { return "\ue8b2"; }
    static QString reset_tv() { return "\ue9d9"; }
    static QString restaurant() { return "\ue56c"; }
    static QString restaurant_menu() { return "\ue561"; }
    static QString restore() { return "\ue8b3"; }
    static QString restore_from_trash() { return "\ue938"; }
    static QString restore_page() { return "\ue929"; }
    static QString ring_volume() { return "\ue0d1"; }
    static QString room() { return "\ue8b4"; }
    static QString room_service() { return "\ueb49"; }
    static QString rotate_90_degrees_ccw() { return "\ue418"; }
    static QString rotate_left() { return "\ue419"; }
    static QString rotate_right() { return "\ue41a"; }
    static QString rounded_corner() { return "\ue920"; }
    static QString router() { return "\ue328"; }
    static QString rowing() { return "\ue921"; }
    static QString rss_feed() { return "\ue0e5"; }
    static QString rtt() { return "\ue9ad"; }
    static QString rv_hookup() { return "\ue642"; }
    static QString satellite() { return "\ue562"; }
    static QString save() { return "\ue161"; }
    static QString save_alt() { return "\ue171"; }
    static QString saved_search() { return "\uea11"; }
    static QString scanner() { return "\ue329"; }
    static QString scatter_plot() { return "\ue268"; }
    static QString schedule() { return "\ue8b5"; }
    static QString schedule_send() { return "\uea0a"; }
    static QString school() { return "\ue80c"; }
    static QString score() { return "\ue269"; }
    static QString screen_lock_landscape() { return "\ue1be"; }
    static QString screen_lock_portrait() { return "\ue1bf"; }
    static QString screen_lock_rotation() { return "\ue1c0"; }
    static QString screen_rotation() { return "\ue1c1"; }
    static QString screen_share() { return "\ue0e2"; }
    static QString sd() { return "\ue9dd"; }
    static QString sd_card() { return "\ue623"; }
    static QString sd_storage() { return "\ue1c2"; }
    static QString search() { return "\ue8b6"; }
    static QString security() { return "\ue32a"; }
    static QString segment() { return "\ue94b"; }
    static QString select_all() { return "\ue162"; }
    static QString send() { return "\ue163"; }
    static QString send_and_archive() { return "\uea0c"; }
    static QString sentiment_dissatisfied() { return "\ue811"; }
    static QString sentiment_neutral() { return "\ue812"; }
    static QString sentiment_satisfied() { return "\ue813"; }
    static QString sentiment_satisfied_alt() { return "\ue0ed"; }
    static QString sentiment_very_dissatisfied() { return "\ue814"; }
    static QString sentiment_very_satisfied() { return "\ue815"; }
    static QString settings() { return "\ue8b8"; }
    static QString settings_applications() { return "\ue8b9"; }
    static QString settings_backup_restore() { return "\ue8ba"; }
    static QString settings_bluetooth() { return "\ue8bb"; }
    static QString settings_brightness() { return "\ue8bd"; }
    static QString settings_cell() { return "\ue8bc"; }
    static QString settings_display() { return "\ue8bd"; }
    static QString settings_ethernet() { return "\ue8be"; }
    static QString settings_input_antenna() { return "\ue8bf"; }
    static QString settings_input_component() { return "\ue8c0"; }
    static QString settings_input_composite() { return "\ue8c1"; }
    static QString settings_input_hdmi() { return "\ue8c2"; }
    static QString settings_input_svideo() { return "\ue8c3"; }
    static QString settings_overscan() { return "\ue8c4"; }
    static QString settings_phone() { return "\ue8c5"; }
    static QString settings_power() { return "\ue8c6"; }
    static QString settings_remote() { return "\ue8c7"; }
    static QString settings_system_daydream() { return "\ue1c3"; }
    static QString settings_voice() { return "\ue8c8"; }
    static QString share() { return "\ue80d"; }
    static QString shield() { return "\ue9e0"; }
    static QString shop() { return "\ue8c9"; }
    static QString shop_two() { return "\ue8ca"; }
    static QString shopping_basket() { return "\ue8cb"; }
    static QString shopping_cart() { return "\ue8cc"; }
    static QString short_text() { return "\ue261"; }
    static QString show_chart() { return "\ue6e1"; }
    static QString shuffle() { return "\ue043"; }
    static QString shuffle_on() { return "\ue9e1"; }
    static QString shutter_speed() { return "\ue43d"; }
    static QString signal_cellular_4_bar() { return "\ue1c8"; }
    static QString signal_cellular_alt() { return "\ue202"; }
    static QString signal_cellular_connected_no_internet_4_bar() { return "\ue1cd"; }
    static QString signal_cellular_no_sim() { return "\ue1ce"; }
    static QString signal_cellular_null() { return "\ue1cf"; }
    static QString signal_cellular_off() { return "\ue1d0"; }
    static QString signal_wifi_4_bar() { return "\ue1d8"; }
    static QString signal_wifi_4_bar_lock() { return "\ue1d9"; }
    static QString signal_wifi_off() { return "\ue1da"; }
    static QString sim_card() { return "\ue32b"; }
    static QString sim_card_alert() { return "\ue624"; }
    static QString single_bed() { return "\uea48"; }
    static QString skip_next() { return "\ue044"; }
    static QString skip_previous() { return "\ue045"; }
    static QString slideshow() { return "\ue41b"; }
    static QString slow_motion_video() { return "\ue068"; }
    static QString smartphone() { return "\ue32c"; }
    static QString smoke_free() { return "\ueb4a"; }
    static QString smoking_rooms() { return "\ueb4b"; }
    static QString sms() { return "\ue625"; }
    static QString sms_failed() { return "\ue626"; }
    static QString snooze() { return "\ue046"; }
    static QString sort() { return "\ue164"; }
    static QString sort_by_alpha() { return "\ue053"; }
    static QString spa() { return "\ueb4c"; }
    static QString space_bar() { return "\ue256"; }
    static QString speaker() { return "\ue32d"; }
    static QString speaker_group() { return "\ue32e"; }
    static QString speaker_notes() { return "\ue8cd"; }
    static QString speaker_notes_off() { return "\ue92a"; }
    static QString speaker_phone() { return "\ue0d2"; }
    static QString speed() { return "\ue9e4"; }
    static QString spellcheck() { return "\ue8ce"; }
    static QString sports() { return "\uea30"; }
    static QString sports_baseball() { return "\uea51"; }
    static QString sports_basketball() { return "\uea26"; }
    static QString sports_cricket() { return "\uea27"; }
    static QString sports_esports() { return "\uea28"; }
    static QString sports_football() { return "\uea29"; }
    static QString sports_golf() { return "\uea2a"; }
    static QString sports_handball() { return "\uea33"; }
    static QString sports_hockey() { return "\uea2b"; }
    static QString sports_kabaddi() { return "\uea34"; }
    static QString sports_mma() { return "\uea2c"; }
    static QString sports_motorsports() { return "\uea2d"; }
    static QString sports_rugby() { return "\uea2e"; }
    static QString sports_soccer() { return "\uea2f"; }
    static QString sports_tennis() { return "\uea32"; }
    static QString sports_volleyball() { return "\uea31"; }
    static QString square_foot() { return "\uea49"; }
    static QString stacked_bar_chart() { return "\ue9e6"; }
    static QString star() { return "\ue838"; }
    static QString star_border() { return "\ue83a"; }
    static QString star_half() { return "\ue839"; }
    static QString star_outline() { return "\ue83a"; }
    static QString stars() { return "\ue8d0"; }
    static QString stay_current_landscape() { return "\ue0d3"; }
    static QString stay_current_portrait() { return "\ue0d4"; }
    static QString stay_primary_landscape() { return "\ue0d5"; }
    static QString stay_primary_portrait() { return "\ue0d6"; }
    static QString stop() { return "\ue047"; }
    static QString stop_screen_share() { return "\ue0e3"; }
    static QString storage() { return "\ue1db"; }
    static QString store() { return "\ue8d1"; }
    static QString store_mall_directory() { return "\ue563"; }
    static QString storefront() { return "\uea12"; }
    static QString straighten() { return "\ue41c"; }
    static QString stream() { return "\ue9e9"; }
    static QString streetview() { return "\ue56e"; }
    static QString strikethrough_s() { return "\ue257"; }
    static QString style() { return "\ue41d"; }
    static QString subdirectory_arrow_left() { return "\ue5d9"; }
    static QString subdirectory_arrow_right() { return "\ue5da"; }
    static QString subject() { return "\ue8d2"; }
    static QString subscriptions() { return "\ue064"; }
    static QString subtitles() { return "\ue048"; }
    static QString subway() { return "\ue56f"; }
    static QString supervised_user_circle() { return "\ue939"; }
    static QString supervisor_account() { return "\ue8d3"; }
    static QString surround_sound() { return "\ue049"; }
    static QString swap_calls() { return "\ue0d7"; }
    static QString swap_horiz() { return "\ue8d4"; }
    static QString swap_horizontal_circle() { return "\ue933"; }
    static QString swap_vert() { return "\ue8d5"; }
    static QString swap_vert_circle() { return "\ue8d6"; }
    static QString swap_vertical_circle() { return "\ue8d6"; }
    static QString swipe() { return "\ue9ec"; }
    static QString switch_account() { return "\ue9ed"; }
    static QString switch_camera() { return "\ue41e"; }
    static QString switch_video() { return "\ue41f"; }
    static QString sync() { return "\ue627"; }
    static QString sync_alt() { return "\uea18"; }
    static QString sync_disabled() { return "\ue628"; }
    static QString sync_problem() { return "\ue629"; }
    static QString system_update() { return "\ue62a"; }
    static QString system_update_alt() { return "\ue8d7"; }
    static QString system_update_tv() { return "\ue8d7"; }
    static QString tab() { return "\ue8d8"; }
    static QString tab_unselected() { return "\ue8d9"; }
    static QString table_chart() { return "\ue265"; }
    static QString tablet() { return "\ue32f"; }
    static QString tablet_android() { return "\ue330"; }
    static QString tablet_mac() { return "\ue331"; }
    static QString tag() { return "\ue9ef"; }
    static QString tag_faces() { return "\ue420"; }
    static QString takeout_dining() { return "\uea74"; }
    static QString tap_and_play() { return "\ue62b"; }
    static QString terrain() { return "\ue564"; }
    static QString text_fields() { return "\ue262"; }
    static QString text_format() { return "\ue165"; }
    static QString text_rotate_up() { return "\ue93a"; }
    static QString text_rotate_vertical() { return "\ue93b"; }
    static QString text_rotation_angledown() { return "\ue93c"; }
    static QString text_rotation_angleup() { return "\ue93d"; }
    static QString text_rotation_down() { return "\ue93e"; }
    static QString text_rotation_none() { return "\ue93f"; }
    static QString textsms() { return "\ue0d8"; }
    static QString texture() { return "\ue421"; }
    static QString theater_comedy() { return "\uea66"; }
    static QString theaters() { return "\ue8da"; }
    static QString thumb_down() { return "\ue8db"; }
    static QString thumb_down_alt() { return "\ue816"; }
    static QString thumb_down_off_alt() { return "\ue9f2"; }
    static QString thumb_up() { return "\ue8dc"; }
    static QString thumb_up_alt() { return "\ue817"; }
    static QString thumb_up_off_alt() { return "\ue9f3"; }
    static QString thumbs_up_down() { return "\ue8dd"; }
    static QString time_to_leave() { return "\ue62c"; }
    static QString timelapse() { return "\ue422"; }
    static QString timeline() { return "\ue922"; }
    static QString timer() { return "\ue425"; }
    static QString timer_10() { return "\ue423"; }
    static QString timer_3() { return "\ue424"; }
    static QString timer_off() { return "\ue426"; }
    static QString title() { return "\ue264"; }
    static QString toc() { return "\ue8de"; }
    static QString today() { return "\ue8df"; }
    static QString toggle_off() { return "\ue9f5"; }
    static QString toggle_on() { return "\ue9f6"; }
    static QString toll() { return "\ue8e0"; }
    static QString tonality() { return "\ue427"; }
    static QString touch_app() { return "\ue913"; }
    static QString toys() { return "\ue332"; }
    static QString track_changes() { return "\ue8e1"; }
    static QString traffic() { return "\ue565"; }
    static QString train() { return "\ue570"; }
    static QString tram() { return "\ue571"; }
    static QString transfer_within_a_station() { return "\ue572"; }
    static QString transform() { return "\ue428"; }
    static QString transit_enterexit() { return "\ue579"; }
    static QString translate() { return "\ue8e2"; }
    static QString trending_down() { return "\ue8e3"; }
    static QString trending_flat() { return "\ue8e4"; }
    static QString trending_neutral() { return "\ue8e4"; }
    static QString trending_up() { return "\ue8e5"; }
    static QString trip_origin() { return "\ue57b"; }
    static QString tune() { return "\ue429"; }
    static QString turned_in() { return "\ue8e6"; }
    static QString turned_in_not() { return "\ue8e7"; }
    static QString tv() { return "\ue333"; }
    static QString tv_off() { return "\ue647"; }
    static QString two_wheeler() { return "\ue9f9"; }
    static QString unarchive() { return "\ue169"; }
    static QString undo() { return "\ue166"; }
    static QString unfold_less() { return "\ue5d6"; }
    static QString unfold_more() { return "\ue5d7"; }
    static QString unsubscribe() { return "\ue0eb"; }
    static QString update() { return "\ue923"; }
    static QString upload_file() { return "\ue9fc"; }
    static QString usb() { return "\ue1e0"; }
    static QString verified_user() { return "\ue8e8"; }
    static QString vertical_align_bottom() { return "\ue258"; }
    static QString vertical_align_center() { return "\ue259"; }
    static QString vertical_align_top() { return "\ue25a"; }
    static QString vertical_split() { return "\ue949"; }
    static QString vibration() { return "\ue62d"; }
    static QString video_call() { return "\ue070"; }
    static QString video_collection() { return "\ue04a"; }
    static QString video_label() { return "\ue071"; }
    static QString video_library() { return "\ue04a"; }
    static QString videocam() { return "\ue04b"; }
    static QString videocam_off() { return "\ue04c"; }
    static QString videogame_asset() { return "\ue338"; }
    static QString view_agenda() { return "\ue8e9"; }
    static QString view_array() { return "\ue8ea"; }
    static QString view_carousel() { return "\ue8eb"; }
    static QString view_column() { return "\ue8ec"; }
    static QString view_comfortable() { return "\ue42a"; }
    static QString view_comfy() { return "\ue42a"; }
    static QString view_compact() { return "\ue42b"; }
    static QString view_day() { return "\ue8ed"; }
    static QString view_headline() { return "\ue8ee"; }
    static QString view_in_ar() { return "\ue9fe"; }
    static QString view_list() { return "\ue8ef"; }
    static QString view_module() { return "\ue8f0"; }
    static QString view_quilt() { return "\ue8f1"; }
    static QString view_stream() { return "\ue8f2"; }
    static QString view_week() { return "\ue8f3"; }
    static QString vignette() { return "\ue435"; }
    static QString visibility() { return "\ue8f4"; }
    static QString visibility_off() { return "\ue8f5"; }
    static QString voice_chat() { return "\ue62e"; }
    static QString voice_over_off() { return "\ue94a"; }
    static QString voicemail() { return "\ue0d9"; }
    static QString volume_down() { return "\ue04d"; }
    static QString volume_mute() { return "\ue04e"; }
    static QString volume_off() { return "\ue04f"; }
    static QString volume_up() { return "\ue050"; }
    static QString volunteer_activism() { return "\uea70"; }
    static QString vpn_key() { return "\ue0da"; }
    static QString vpn_lock() { return "\ue62f"; }
    static QString wallet_giftcard() { return "\ue8f6"; }
    static QString wallet_membership() { return "\ue8f7"; }
    static QString wallet_travel() { return "\ue8f8"; }
    static QString wallpaper() { return "\ue1bc"; }
    static QString warning() { return "\ue002"; }
    static QString watch() { return "\ue334"; }
    static QString watch_later() { return "\ue924"; }
    static QString waterfall_chart() { return "\uea00"; }
    static QString waves() { return "\ue176"; }
    static QString wb_auto() { return "\ue42c"; }
    static QString wb_cloudy() { return "\ue42d"; }
    static QString wb_incandescent() { return "\ue42e"; }
    static QString wb_iridescent() { return "\ue436"; }
    static QString wb_shade() { return "\uea01"; }
    static QString wb_sunny() { return "\ue430"; }
    static QString wb_twighlight() { return "\uea02"; }
    static QString wc() { return "\ue63d"; }
    static QString web() { return "\ue051"; }
    static QString web_asset() { return "\ue069"; }
    static QString weekend() { return "\ue16b"; }
    static QString whatshot() { return "\ue80e"; }
    static QString where_to_vote() { return "\ue177"; }
    static QString widgets() { return "\ue1bd"; }
    static QString wifi() { return "\ue63e"; }
    static QString wifi_lock() { return "\ue1e1"; }
    static QString wifi_off() { return "\ue648"; }
    static QString wifi_tethering() { return "\ue1e2"; }
    static QString work() { return "\ue8f9"; }
    static QString work_off() { return "\ue942"; }
    static QString work_outline() { return "\ue943"; }
    static QString workspaces_filled() { return "\uea0d"; }
    static QString workspaces_outline() { return "\uea0f"; }
    static QString wrap_text() { return "\ue25b"; }
    static QString youtube_searched_for() { return "\ue8fa"; }
    static QString zoom_in() { return "\ue8ff"; }
    static QString zoom_out() { return "\ue900"; }
    static QString zoom_out_map() { return "\ue56b"; }

signals:
    void changed();

private:
    Shade m_shade = Shade500;
};

#endif // MATERIAL_H
