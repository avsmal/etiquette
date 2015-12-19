import sys
import os
from gi.repository import Gtk, Gdk, GLib, AppIndicator3 as appindicator
from datetime import datetime
from functools import partial


class Applet:
    def __init__(self, data_base, update_timer_t=5, timeout=30):
        self.timeout = timeout
        self.count = 0
        self.db = data_base
        self.update_timer_t = update_timer_t
        self.timeout = timeout

    def show(self):
        self.ind = self._make_indicator()
        self._download_messages()
        self.menu = self._make_menu()

        self.ind.set_menu(self.menu)
        self.menu.show_all()
        GLib.timeout_add_seconds(self.update_timer_t, self._update)
        Gtk.main()

    def _sub_menu(self, menu_items, menu, msg):
        sub_menu = Gtk.Menu()
        item1 = Gtk.MenuItem('ignore')
        item2 = Gtk.MenuItem('answer')

        ignore_f = partial(self._ignore, menu_item=menu_items, menu=menu, msg=msg)
        answer_f = partial(self._answer, menu_item=menu_items, menu=menu, msg=msg)
        item1.connect('activate', ignore_f)
        item2.connect('activate', answer_f)

        sub_menu.append(item1)
        sub_menu.append(item2)

        return sub_menu

    def _make_block_menu(self, name, messages, menu):
        for msg in messages:
            menu_items = Gtk.MenuItem(self._make_label(msg))
            menu_items.set_submenu(self._sub_menu(menu_items, menu, msg))
            menu.append(menu_items)
        sep_menu = Gtk.SeparatorMenuItem()
        menu.append(sep_menu)

    def _make_indicator(self):
        ind = appindicator.Indicator.new("example-simple-client",
                                         os.path.abspath('gtk-apply_6028.ico'),
                                         appindicator.IndicatorCategory.APPLICATION_STATUS)
        ind.set_status(appindicator.IndicatorStatus.ACTIVE)
        s = os.path.split(os.path.abspath(__file__))[0]
        s = os.path.join(s, 'icons', 'head.ico')
        ind.set_icon(s)
        return ind

    def _answer(self, widget, menu_item, menu, msg):
        self.db.add_answered(msg)
        menu.remove(menu_item)

    def _ignore(self, widget, menu_item, menu, msg):
        self.db.add_ignored(msg)
        self._update()

    def _make_menu(self):
        blocks = (('Recently', self.recently), ('Long', self.long),
                  ('Long long', self.long_long))
        menu = Gtk.Menu()
        for name, messages in blocks:
            img = Gtk.Image()
            s = os.path.split(os.path.abspath(__file__))[0]
            s = os.path.join(s, 'icons', name + '.png')
            img.set_from_file(s)
            img.show()
            title = Gtk.ImageMenuItem(Gtk.STOCK_NEW, name)
            title.get_children()[0].set_label(name)
            title.set_image(img)
            title.set_always_show_image(True)
            menu.append(title)
            self._make_block_menu(name, messages, menu)
        menu.append(self._make_quit())
        return menu

    def _update(self):
        self._download_messages()
        self.menu = self._make_menu()
        self.ind.set_menu(self.menu)
        self.menu.show_all()
        return True

    def _make_quit(self):
        quit_item = Gtk.MenuItem("Quit")
        quit_item.connect("activate", self._quit)
        return quit_item

    def _download_messages(self):
        self.recently, self.long, self.long_long = self.db.get_messages()

    def _make_label(self, msg):
        label = "{}:\n {}\n {} time:{}:{}:{}"
        sec = int((datetime.utcnow() - msg.date).total_seconds())

        hour = sec // 3600
        minutes = (sec - hour * 3600) // 60
        sec = (sec - hour * 3600 - minutes * 60)

        return label.format(msg.to, msg.sender, msg.subject, hour, minutes, sec)

    def _quit(self, widget):
        sys.exit(0)
