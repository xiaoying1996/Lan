#include "WebSocketClient.h"
#include <QDebug>

WebSocketClient::WebSocketClient(const QUrl& url, QObject* parent)
    : QObject(parent), m_url(url), m_isConnected(false)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    connect(&m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &WebSocketClient::onError);

    m_webSocket.open(m_url);
}

WebSocketClient::~WebSocketClient()
{
    if (m_isConnected) {
        m_webSocket.close();
    }
}

void WebSocketClient::sendMessage(const QString& message)
{
    if (m_isConnected) {
        m_webSocket.sendTextMessage(message);
    }
    else {
        qWarning() << "Not connected, cannot send message";
    }
}

void WebSocketClient::onConnected()
{
    m_isConnected = true;
    qDebug() << "WebSocket connected to" << m_url.toString();
    emit connected();
}

void WebSocketClient::onDisconnected()
{
    m_isConnected = false;
    qDebug() << "WebSocket disconnected";
    emit disconnected();
}

void WebSocketClient::onTextMessageReceived(const QString& message)
{
    qDebug() << "Message received:" << message;
    emit messageReceived(message);
}

void WebSocketClient::onError(QAbstractSocket::SocketError error)
{
    QString errorStr = QString("WebSocket error: %1").arg(m_webSocket.errorString());
    qWarning() << errorStr;
    emit errorOccurred(errorStr);
}