#ifndef CLIENTE_H
#define CLIENTE_H

#include <QTcpSocket>
#include <QObject>

class Cliente : public QObject {
    Q_OBJECT

public:
    explicit Cliente(QObject *parent = nullptr);
    void conectarAoServidor(QString enderecoIP, quint16 porta);
    void enviarMensagem(QString mensagem);

signals:
    void mensagemRecebida(QString mensagem);
    void conectado();

private slots:
    void dadosRecebidos();
    void erroDeConexao(QAbstractSocket::SocketError erro);

private:
    QTcpSocket *socket;
};

#endif // CLIENTE_H
