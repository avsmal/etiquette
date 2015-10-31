#pragma once
#include <vmime/vmime.hpp>

class interactiveCertificateVerifier : public vmime::security::cert::defaultCertificateVerifier
{
	public:
	void verify(vmime::shared_ptr <vmime::security::cert::certificateChain> chain, const vmime::string& hostname);

	private:
	std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate> > m_trustedCerts;
};


