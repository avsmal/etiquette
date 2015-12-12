# -*- coding: utf-8 -*-
import random
import time
from FilterMessages import FilterMessages
from datetime import datetime
from collections import namedtuple
from accounts import AccountsPy

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

Message = namedtuple('Message', ['sender', 'to', 'date', 'subject', 'body'])


def add_date(imap_messages):
    messages = []
    for mail, senders in imap_messages:
        ls = [mail]
        msgs = []
        for sender in senders:
            rand_data = datetime.fromtimestamp(
                time.time() - random.randint(0, 100))
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


def get_text_part(msg_body):
    parts = msg_body.split('Content-Type:')
    answer = []
    for part in parts:
        s_part = part.strip(' ')
        if s_part.startswith('text/plain'):
            answer.append(s_part)
    return answer


class Server:
    def __init__(self, path_config, enable_filter=True):
        self.accounts = AccountsPy(path_config)
        self.enable_filter = enable_filter
        self.filter = FilterMessages()

    def download_messages(self, time):
        delta_t = (datetime.utcnow() - datetime(1970, 1, 1)).total_seconds() - time
        imap_messages = self.accounts.getMessages(int(delta_t))
        self.messages = self._make_messages(imap_messages)
        return self.messages

    def _make_messages(self, imap_messages):
        answer = []
        for msg in imap_messages:
            to, sender = msg[0], msg[1]
            date = datetime(msg[2][0], msg[2][1], msg[2][2], msg[2][3],
                            msg[2][4], msg[2][5])
            body_text = '\n'.join(get_text_part(msg[4]))
            new_msg = Message(sender, to, date, msg[3], body_text)
            if self.enable_filter and self.filter(new_msg):
                answer.append(new_msg)
        return answer