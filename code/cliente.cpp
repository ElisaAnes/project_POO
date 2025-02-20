#include "cliente.h"
#include <QDebug>

Cliente::Cliente(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {
    connect(socket, &QTcpSocket::readyRead, this, &Cliente::dadosRecebidos);
    connect(socket, &QTcpSocket::connected, this, &Cliente::conectado);
    connect(socket, &QTcpSocket::errorOccurred, this, &Cliente::erroDeConexao); // 🔹 Correção aqui!
}

void Cliente::conectarAoServidor(QString enderecoIP, quint16 porta) {
    socket->connectToHost(QHostAddress(enderecoIP), porta);
}

void Cliente::dadosRecebidos() {
    QString mensagem = socket->readAll();
    qDebug() << "Mensagem recebida:" << mensagem;
    emit mensagemRecebida(mensagem);
}

void Cliente::erroDeConexao(QAbstractSocket::SocketError erro) {
    qDebug() << "Erro na conexão:" << erro;
}

void Cliente::enviarMensagem(QString mensagem) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(mensagem.toUtf8());
        socket->flush();
    }
}
