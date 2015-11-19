#pragma once
#include <vmime/vmime.hpp>

class interactiveCertificateVerifier : public vmime::security::cert::defaultCertificateVerifier
{
public:

	void verify(vmime::ref <vmime::security::cert::certificateChain> chain);

private:

	static std::vector <vmime::ref <vmime::security::cert::X509Certificate> > m_trustedCerts;
};

