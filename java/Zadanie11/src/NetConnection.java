/**
 * Ogólny interfejs pozwalający na obsługę połączeń sieciowych.
 */
public interface NetConnection {
	/**
	 * Program otwiera połączenie do serwera dostępnego protokołem TCP/IP pod adresem
	 * host i numerem portu TCP port, wykonuje swoje zadanie i zamyka połączenie.
	 * 
	 * @param host adres IP lub nazwa komputera
	 * @param port numer portu, na którym serwer oczekuje na połączenie
	 */
	public void connectExecuteClose(String host, int port);
}
