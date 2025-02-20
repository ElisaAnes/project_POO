#include "servidor.h"
#include <QDebug>

Servidor::Servidor(QObject *parent) : QObject(parent), servidor(new QTcpServer(this)), socketCliente(nullptr) {
    connect(servidor, &QTcpServer::newConnection, this, &Servidor::novaConexao);
}

void Servidor::iniciarServidor(quint16 porta) {
    if (servidor->listen(QHostAddress::Any, porta)) {
        qDebug() << "Servidor iniciado na porta" << porta;
    } else {
        qDebug() << "Erro ao iniciar o servidor:" << servidor->errorString();
    }
}

void Servidor::novaConexao() {
    socketCliente = servidor->nextPendingConnection();
    connect(socketCliente, &QTcpSocket::readyRead, this, &Servidor::dadosRecebidos);
    emit jogadorConectado();
    qDebug() << "Jogador conectado!";
}

void Servidor::dadosRecebidos() {
    if (socketCliente) {
        QString mensagem = socketCliente->readAll();
        qDebug() << "Mensagem recebida:" << mensagem;
        emit mensagemRecebida(mensagem);
    }
}

void Servidor::enviarMensagem(QString mensagem) {
    if (socketCliente) {
        socketCliente->write(mensagem.toUtf8());
        socketCliente->flush();
    }
}
