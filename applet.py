#!/usr/bin/env python
from gi.repository import Gtk
from gi.repository import AppIndicator3 as appindicator
from gi.repository import GLib
from messagesmodule import *


class Applet:
    def __init__(self, timeout, limit=5):
        self.timeout = timeout
        self.limit = limit
        self.count = 0
    def __call__(self):
        while True:
            ind = appindicator.Indicator.new("example-simple-client", "indicator-messages", appindicator.IndicatorCategory.APPLICATION_STATUS)
            ind.set_status(appindicator.IndicatorStatus.ACTIVE)
            ind.set_attention_icon("indicator-messages-new")

            menu = Gtk.Menu()
            
            for email in getMessages():
                menu_items = Gtk.MenuItem(email)
                menu.append(menu_items)
                menu_items.show()
           
            ind.set_menu(menu)
            GLib.timeout_add_seconds(self.timeout, self.end)
            Gtk.main()
            if self.count == self.limit:
                break

    def end(self):
        self.count += 1
        Gtk.main_quit()

applet = Applet(15)
applet()
