#!/usr/bin/env python
from gi.repository import Gtk
from gi.repository import AppIndicator3 as appindicator
from messagesmodule import *

def app_let_indicator():
    ind = appindicator.Indicator.new(
        "example-simple-client",
        "indicator-messages",
        appindicator.IndicatorCategory.APPLICATION_STATUS)
    ind.set_status(appindicator.IndicatorStatus.ACTIVE)
    ind.set_attention_icon("indicator-messages-new")

    menu = Gtk.Menu()

    for el in getMessages():
        buf = el
        menu_items = Gtk.MenuItem(buf)
        menu.append(menu_items)
        menu_items.show()
    ind.set_menu(menu)
    Gtk.main()

app_let_indicator();
