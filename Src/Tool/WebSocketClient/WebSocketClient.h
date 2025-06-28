#ifndef _WEBSOCKETCLIENT_
#define _WEBSOCKETCLIENT_

#include <QObject>
#include <QWebSocket>
#include <QUrl>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(const QUrl& url, QObject* parent = nullptr);
    ~WebSocketClient();

    void sendMessage(const QString& message);

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString& message);
    void errorOccurred(const QString& error);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString& message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_isConnected;
};
#endif // !