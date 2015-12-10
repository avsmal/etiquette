import random
import time
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

Message = namedtuple('Message', ['sender', 'to', 'date'])


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


class Server:
    def __init__(self, path_config):
        self.messages = make_messages(add_date(TestMail))
        self.accounts = AccountsPy(path_config)

    def download_messages(self, date):
        imap_messages = self.accounts.getMessages(int((datetime.now() - datetime(1970, 1, 1)).total_seconds() - 5000000))
        self.messages = self._make_messages(imap_messages)
        return self.messages

    def _make_messages(self, imap_messages):
        answer = []
        for msg in imap_messages:
            to, sender = msg[0]
            date = datetime(msg[1][0], msg[1][1], msg[1][2], msg[1][3],
                            msg[1][4], msg[1][5])
            answer.append(Message(sender, to, date))
        return answer
