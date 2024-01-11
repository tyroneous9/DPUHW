public class CurrentMarketTracker {
    private static CurrentMarketTracker instance = new CurrentMarketTracker();
    private CurrentMarketPublisher publisher;

    private CurrentMarketTracker() {
        publisher = CurrentMarketPublisher.getInstance();
    }

    public static CurrentMarketTracker getInstance() {
        return instance;
    }

    public void updateMarket(String symbol, Price buyPrice, int buyVolume, Price sellPrice, int sellVolume) {
        Price marketWidth;
        if(buyPrice != null && sellPrice != null)
            marketWidth = sellPrice.subtract(buyPrice);
        else {
            marketWidth = new Price(0);
        }

        CurrentMarketSide buySide = new CurrentMarketSide(buyPrice, buyVolume);
        CurrentMarketSide sellSide = new CurrentMarketSide(sellPrice, sellVolume);

        System.out.println("*********** Current Market ***********");
        System.out.printf("* %s     %s - %s [%s]\n", symbol, buySide.toString(), buySide.toString(), marketWidth.toString());
        System.out.println("**************************************");

        publisher.acceptCurrentMarket(symbol, buySide, sellSide);
    }
}
