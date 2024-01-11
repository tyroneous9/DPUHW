import java.util.HashMap;

public class User implements CurrentMarketObserver {
    private String userId;
    private HashMap<String, OrderDTO> orders = new HashMap<>();
    private HashMap<String, CurrentMarketSide[]> currentMarkets;
    public User(String userId) throws DataValidationException {
        setUserId(userId);
        currentMarkets = new HashMap<>();
    }
    
    public String getUserId() {
        return userId;
    }

    private void setUserId(String userId) throws DataValidationException {
        if (userId != null && userId.matches("^[A-Z]{3}$")) {
            this.userId = userId;
        } else {
            throw new DataValidationException("Invalid userId");
        }
    }

    public void addOrder(OrderDTO o) throws OrderNotFoundException {
        if(o == null) throw new OrderNotFoundException("Order not found");
        else orders.put(o.id, o);
    }

    public boolean hasOrderWithRemainingQty() {
        for (OrderDTO order : orders.values()) {
            if (order.remainingVolume > 0) return true;
        }
        return false;
    }

    public OrderDTO getOrderWithRemainingQty() {
        for (OrderDTO order : orders.values()) {
            if (order.remainingVolume > 0) return order;
        }
        return null;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("User Id: ").append(userId).append("\n");
        for (OrderDTO order : orders.values()) {
            String str = "Product: " + order.product + ", Price: " + order.price.toString() +
                    ", OriginalVolume: " + order.originalVolume + ", RemainingVolume: " + order.remainingVolume +
                    ", CancelledVolume: " + order.cancelledVolume + ", FilledVolume: " + order.filledVolume +
                    ", User: " + order.user + ", Side: " + order.side + ", Id: " + order.id;
            result.append(str+"\n");
        }
        return result.toString();
    }

    @Override
    public void updateCurrentMarket(String symbol, CurrentMarketSide buySide, CurrentMarketSide sellSide) {
        CurrentMarketSide[] updatedMarket = new CurrentMarketSide[]{buySide, sellSide};
        currentMarkets.put(symbol, updatedMarket);
    }

    public String getCurrentMarkets() {
        StringBuilder summary = new StringBuilder();
        for (String symbol : currentMarkets.keySet()) {
            CurrentMarketSide[] market = currentMarkets.get(symbol);
            String str = String.format("%s     %s - %s\n", symbol, market[0].toString(), market[1].toString());
            summary.append(str);
        }
        return summary.toString();

    }

}
