import java.util.ArrayList;
import java.util.HashMap;

public class CurrentMarketPublisher {
    private static CurrentMarketPublisher instance = new CurrentMarketPublisher();
    private HashMap<String, ArrayList<CurrentMarketObserver>> filters;

    private CurrentMarketPublisher() {
        filters = new HashMap<>();
    }

    public static CurrentMarketPublisher getInstance() {
        return instance;
    }

    public void subscribeCurrentMarket(String symbol, CurrentMarketObserver cmo) {
        ArrayList<CurrentMarketObserver> observers = filters.get(symbol);

        if (observers == null) {
            observers = new ArrayList<>();
            filters.put(symbol, observers);
        }

        observers.add(cmo);
    }

    public void unSubscribeCurrentMarket(String symbol, CurrentMarketObserver cmo) {
        ArrayList<CurrentMarketObserver> observers = filters.get(symbol);

        if (observers != null) {
            observers.remove(cmo);
        }
    }

    public void acceptCurrentMarket(String symbol, CurrentMarketSide buySide, CurrentMarketSide sellSide) {
        if (!filters.containsKey(symbol)) {
            return;
        }
        ArrayList<CurrentMarketObserver> observers = filters.get(symbol);
        for (CurrentMarketObserver observer : observers) {
            observer.updateCurrentMarket(symbol, buySide, sellSide);
        }
    }
}
