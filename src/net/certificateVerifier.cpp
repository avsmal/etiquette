#include <vmime/vmime.hpp>
#include <iostream>

#include "certificateVerifier.hpp"
    
std::vector <vmime::ref <vmime::security::cert::X509Certificate> >
    interactiveCertificateVerifier::m_trustedCerts;

void interactiveCertificateVerifier::verify
    (vmime::ref <vmime::security::cert::certificateChain> chain) {
    try {
        setX509TrustedCerts(m_trustedCerts);
        defaultCertificateVerifier::verify(chain);
    } catch (vmime::exceptions::certificate_verification_exception&) {
        vmime::ref <vmime::security::cert::certificate> cert = chain->getAt(0);
        std::cout << std::endl;
        std::cout << "Server sent a '" << cert->getType() << "'" << " certificate." << std::endl;

            // Accept it, and remember user's choice for later
        if (cert->getType() == "X.509") {
            m_trustedCerts.push_back(cert.dynamicCast
            <vmime::security::cert::X509Certificate>());
        }

        return;

        throw vmime::exceptions::certificate_verification_exception
            ("User did not accept the certificate.");
    }
}

