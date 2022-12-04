#include <boost/asio.hpp>
#include <iostream>
using namespace boost::asio;

int main() {
    boost::asio::io_service service;
    boost::asio::ip::tcp::socket sock(service);
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8005));
    acceptor.accept(sock);
    std::cout << "новое подключение\n";
    while (true) {
        std::string command;
        std::getline(std::cin,command);
        sock.write_some(boost::asio::buffer(command));
    }
}
