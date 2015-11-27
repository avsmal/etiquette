from gi.repository import Gtk, Gdk
from gi.repository import AppIndicator3 as appindicator
from gi.repository import GLib
from messagesmodule import *
from collections import namedtuple
from datetime import datetime
import random
import time
import functools

Message = namedtuple('Message', ['sender', 'to', 'date'])

TestMail = [['test.imap2015@mail.ru',
             ['mailapps@corp.mail.ru', 'welcome@corp.mail.ru',
              'bagman_2008@mail.ru', 'agent@corp.mail.ru',
              'test.imap2015@mail.ru']],
            ['test.imap2016@mail.ru', ['welcome@corp.mail.ru']],
            ['test.imap2017@mail.ru',
             ['welcome@corp.mail.ru', 'mailapps@corp.mail.ru',
              'welcome@corp.mail.ru']], ['test.imap2018@mail.ru',
                                         ['welcome@corp.mail.ru',
                                          'mailapps@corp.mail.ru',
                                          'welcome@corp.mail.ru']]]


class Applet:
    def __init__(self, timeout, limit=5):
        self.timeout = timeout
        self.limit = limit
        self.count = 0

    def __call__(self):
        while True:
            ind = appindicator.Indicator.new("example-simple-client",
                                             "indicator-messages",
                                             appindicator.IndicatorCategory.APPLICATION_STATUS)
            ind.set_status(appindicator.IndicatorStatus.ACTIVE)
            ind.set_attention_icon("indicator-messages-new")

            menu = Gtk.Menu()
            ans = getMessages()
            print(ans)
            for email in ans:
                menu_items = Gtk.MenuItem(email)
                menu_items.get_colormap()
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


def add_date(imap_messages):
    messages = []
    for mail, senders in imap_messages:
        ls = [mail]
        msgs = []
        for sender in senders:
            rand_data = datetime.fromtimestamp(time.time() - random.randint(0, 100))
            msgs.append((sender, rand_data))
        ls.append(msgs)
        messages.append(ls)
    return messages


def make_messages(imap_messages):
    messages = []
    for mail, senders in imap_messages:
        for sender, date in senders:
            msg = Message(sender, mail, date)
            messages.append(msg)
    return messages


class MailDb:
    def __init__(self, recently_time, long_time, long_long_time):
        self.messages = set()
        self.recently_t = recently_time
        self.long_t = long_time
        self.long_long_t = long_long_time

    def update(self, messages):
        for message in messages:
            if message not in self.messages:
                self.messages.add(message)

    def get_messages(self):
        recently = []
        long = []
        long_long = []

        for message in self.messages:
            time = datetime.now() - message.date
            time = time.total_seconds()
            if 0 <= time <= self.recently_t:
                recently.append(message)
            elif self.recently_t <= time <= self.long_t:
                long.append(message)
            elif self.long_t <= time <= self.long_long_t:
                long_long.append(message)
            else:
                del message

        return recently, long, long_long


class NewApplet:
    def __init__(self, timeout, limit=5):
        self.timeout = timeout
        self.limit = limit
        self.count = 0

    def print_msg(self, recently, long, long_long):
        ind = appindicator.Indicator.new("example-simple-client",
                                             "indicator-messages",
                                             appindicator.IndicatorCategory.APPLICATION_STATUS)
        ind.set_status(appindicator.IndicatorStatus.ACTIVE)
        ind.set_attention_icon("indicator-messages-new")

        menu = Gtk.Menu()
        for email in recently:
            menu_items = Gtk.MenuItem(email.to + ' : ' + email.sender)
            menu_items.set_submenu(self._sub_menu(menu_items, menu))
            menu_items.set_style(None)
            menu_items.modify_style(Gtk.RcStyle())
            color = Gdk.color_parse('red')
            menu_items.modify_base(Gtk.StateType.NORMAL, Gdk.color_parse("blue"))
            menu_items.modify_bg(Gtk.StateType.NORMAL, Gdk.color_parse("blue"))
            menu.append(menu_items)
            menu_items.show()

        sep1 = Gtk.SeparatorMenuItem()
        sep1.show()
        menu.append(sep1)
        for email in long:
            menu_items = Gtk.MenuItem(email.to + ' : ' + email.sender)
            menu_items.set_submenu(self._sub_menu(menu_items, menu))
            menu_items.set_style(None)
            menu_items.modify_style(Gtk.RcStyle())
            color = Gdk.color_parse('red')
            menu_items.modify_base(Gtk.StateType.NORMAL, Gdk.color_parse("blue"))
            menu_items.modify_bg(Gtk.StateType.NORMAL, Gdk.color_parse("blue"))
            menu.append(menu_items)
            menu_items.show()

        ind.set_menu(menu)
        Gtk.main()

    def _sub_menu(self, menu_items, menu):
        sub_menu = Gtk.Menu()
        item1 = Gtk.MenuItem('ignore')
        item1.connect('activate', functools.partial(self.ignore, el=menu_items, menu=menu))
        item2 = Gtk.MenuItem('answer')
        item2.connect('activate', self.answer)
        sub_menu.append(item1)
        sub_menu.append(item2)
        item1.show()
        item2.show()
        return sub_menu

    def ignore(self, widget, el, menu):
        menu.remove(el)

    def answer(self, widget):
        print('answer')


if __name__ == '__main__':
    print(add_date(TestMail))
    s = make_messages(add_date(TestMail))
    print(s)
    db = MailDb(10, 15, 20)
    db.update(s)
    l, s, h = db.get_messages()
    print('---------------------')
    print(l)
    print(s)
    print(h)
    ap = NewApplet(100)
    ap.print_msg(l, s, h)