import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class ProductBookSide {
    public enum BookSide {
        BUY, SELL
    }

    private final BookSide side;
    private final HashMap<Price, ArrayList<Order>> bookEntries;

    public ProductBookSide(BookSide side) {
        this.side = side;
        this.bookEntries = new HashMap<>();
    }

    public OrderDTO add(Order o) {
        Price incomingPrice = o.getPrice();
        if (!bookEntries.containsKey(incomingPrice)) {
            bookEntries.put(incomingPrice, new ArrayList<>());
        }
        bookEntries.get(incomingPrice).add(o);
        return o.makeTradableDTO();
    }

    public OrderDTO cancel(String orderId) {
        for (Price price : bookEntries.keySet()) {
            ArrayList<Order> orders = bookEntries.get(price);
            for (Order order : orders) {
                if (order.getId().equals(orderId)) {
                    orders.remove(order);
                    order.setCancelledVolume(order.getCancelledVolume() + order.getRemainingVolume());
                    order.setRemainingVolume(0);

                    if (orders.isEmpty()) {
                        bookEntries.remove(price);
                    }

                    return order.makeTradableDTO();
                }
            }
        }
        return null;
    }

    private ArrayList<Price> getSortedPrices() {
        ArrayList<Price> sorted = new ArrayList<>(bookEntries.keySet());
        Collections.sort(sorted);
        if (side == BookSide.BUY) {
            Collections.reverse(sorted);
        }
        return sorted;
    }

    public Price topOfBookPrice() {
        ArrayList<Price> sorted = getSortedPrices();
        if(sorted.isEmpty())
            return null;
        return sorted.get(0);
    }

    public int topOfBookVolume() {
        Price topPrice = topOfBookPrice();
        if(topPrice == null)
            return 0;
        int totalVol = 0;
        for(Order order : bookEntries.get(topPrice)) {
            totalVol += order.getRemainingVolume();
        }
        return totalVol;
    }

    public void tradeOut(Price price, int vol) {
        int remainingVol = vol;
        ArrayList<Order> orders = bookEntries.get(price);
        while(remainingVol > 0) {
            Order firstOrder = orders.get(0);
            if(firstOrder.getRemainingVolume() <= remainingVol) {
                orders.remove(0);
                int firstOrderRemainingVol = firstOrder.getRemainingVolume();
                firstOrder.setFilledVolume(firstOrder.getFilledVolume() + firstOrderRemainingVol);
                firstOrder.setRemainingVolume(0);
                remainingVol -= firstOrderRemainingVol;
                System.out.println("    FILL: "+"("+side+" "+firstOrderRemainingVol+") "+ firstOrder.toString());
            }
            else {
                firstOrder.setFilledVolume(firstOrder.getFilledVolume() + remainingVol);
                firstOrder.setRemainingVolume(firstOrder.getRemainingVolume() - remainingVol);
                System.out.println("    PARTIAL FILL: "+"("+side+" "+firstOrder.getFilledVolume()+") "+ firstOrder.toString());
                remainingVol = 0;
            }
        }
        if(orders.isEmpty()) {
            bookEntries.remove(price);
        }
    }

//    FILL: (SELL 120) EEE order: SELL TGT at $10.10, Orig Vol: 120, Rem Vol: 0, Fill Vol: 120, CXL Vol: 0, ID: EEETGT$10.1047140634902800
//    PARTIAL FILL: (BUY 10) DDD order: BUY TGT at $10.25, Orig Vol: 100, Rem Vol: 90, Fill Vol: 10, CXL Vol: 0, ID: DDDTGT$10.2547140641496100
//    FILL: (SELL 90) FFF order: SELL TGT at $10.25, Orig Vol: 90, Rem Vol: 0, Fill Vol: 90, CXL Vol: 0, ID: FFFTGT$10.2547140635620100
//    FILL: (BUY 100) DDD order: BUY TGT at $10.25, Orig Vol: 100, Rem Vol: 0, Fill Vol: 100, CXL Vol: 0, ID: DDDTGT$10.2547140641496100

//    FILL: (SELL 10) EEE order: SELL TGT at $10.10, Orig Vol: 120, Rem Vol: 0, Fill Vol: 120, CXL Vol: 0, ID: EEETGT$10.10595271806503100
//    PARTIAL FILL: (BUY 10) DDD order: BUY TGT at $10.25, Orig Vol: 100, Rem Vol: 90, Fill Vol: 10, CXL Vol: 0, ID: DDDTGT$10.25595271827144200
//    FILL: (SELL 90) FFF order: SELL TGT at $10.25, Orig Vol: 90, Rem Vol: 0, Fill Vol: 90, CXL Vol: 0, ID: FFFTGT$10.25595271808923900
//    FILL: (BUY 90) DDD order: BUY TGT at $10.25, Orig Vol: 100, Rem Vol: 0, Fill Vol: 100, CXL Vol: 0, ID: DDDTGT$10.25595271827144200
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("Side: ").append(side).append("\n");
        if(bookEntries.isEmpty()) {
            builder.append("(empty)\n");
        }
        for (Price price : getSortedPrices()) {
            ArrayList<Order> orders = bookEntries.get(price);
            builder.append("    Price: ").append(price.toString()).append("\n");
            for (Order order : orders) {
                builder.append("        ");
                builder.append(order.toString()).append("\n");
            }
        }

        return builder.toString();
    }


}
