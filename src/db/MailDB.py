from datetime import datetime


class MailDB:
    def __init__(self, recently_time, long_time, long_long_time, dow_t, server):
        self.messages = set()
        self.messages_ignore = set()

        self.recently_t = recently_time
        self.long_t = long_time
        self.long_long_t = long_long_time

        self.server = server
        self.dow_t = dow_t
        self.data_last_update = datetime.min

    def _download_messages(self):
        return self.server.download_messages(self.data_last_update)

    def _update(self):
        new_messages = self._download_messages()
        self.data_last_update = datetime.now()

        for message in new_messages:
            if message not in self.messages:
                self.messages.add(message)

    def get_messages(self):
        recently, long, long_long = [], [], []
        delta = (datetime.now() - self.data_last_update).total_seconds()

        if delta > self.dow_t:
            self._update()

        for message in self.messages:
            if message in self.messages_ignore:
                continue
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

    def add_ignored(self, message):
        self.messages_ignore.add(message)
