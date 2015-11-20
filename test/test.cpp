#include <vmime/platforms/posix/posixHandler.hpp> 
#include "../src/net/MailBox.hpp"
#include "../src/net/MailBoxSetting.hpp"
#include <gtest/gtest.h>


// Тестовый класс для тестирования класса Foo.
class MailBoxTest : public ::testing::Test {
 protected:
  // Можете удалить любую или все из функций ниже, если они пустые.

  MailBoxTest() {
		vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
		MailBoxSetting setting_1("test.imap2015@mail.ru", "824222443a", "imap.mail.ru:993");
		MailBox mailbox1(setting_1);
		mailbox1_ = mailbox1;
  }

  MailBox mailbox1_;
};

TEST_F(MailBoxTest, getUnAnswered) {
  mailbox1_.connect();
  EXPECT_EQ(5, mailbox1_.getUnAnswered().size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
