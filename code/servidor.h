#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class Servidor : public QObject {
    Q_OBJECT

public:
    explicit Servidor(QObject *parent = nullptr);
    void iniciarServidor(quint16 porta);
    void enviarMensagem(QString mensagem);

signals:
    void mensagemRecebida(QString mensagem);
    void jogadorConectado();

private slots:
    void novaConexao();
    void dadosRecebidos();

private:
    QTcpServer *servidor;
    QTcpSocket *socketCliente;
};

#endif // SERVIDOR_H
