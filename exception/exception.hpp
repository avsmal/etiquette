#include <exception>


class EtiquetteException : public std::exception {};
class NetException : public EtiquetteException {};

class ConnectException : public NetException {};
class AuthenticationException : public NetException {};

