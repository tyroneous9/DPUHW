import java.util.HashMap;
import java.util.Random;

public class TrafficSim {
    private static HashMap<String, Double> basePrices= new HashMap<>();;

    public static void runSim() throws DataValidationException, OrderNotFoundException {
        String[] testUsers = {"ANN", "BOB", "CAT", "DOG", "EGG"};
        UserManager userManager = UserManager.getInstance();
        userManager.init(testUsers);

        User ANN = userManager.getUser("ANN");
        User BOB = userManager.getUser("BOB");
        User CAT = userManager.getUser("CAT");
        User DOG = userManager.getUser("DOG");
        User EGG = userManager.getUser("EGG");
        CurrentMarketPublisher cmp = CurrentMarketPublisher.getInstance();

        cmp.subscribeCurrentMarket("WMT", ANN);
        cmp.subscribeCurrentMarket("TGT", ANN);
        cmp.subscribeCurrentMarket("TGT", BOB);
        cmp.subscribeCurrentMarket("TSLA", BOB);
        cmp.subscribeCurrentMarket("AMZN", CAT);
        cmp.subscribeCurrentMarket("TGT", CAT);
        cmp.subscribeCurrentMarket("WMT", CAT);
        cmp.subscribeCurrentMarket("TSLA", DOG);
        cmp.subscribeCurrentMarket("WMT", EGG);
        cmp.unSubscribeCurrentMarket("TGT", BOB);

        String[] testSymbols = {"WMT", "TGT", "AMZN", "TSLA"};
        ProductManager productManager = ProductManager.getInstance();
        for(String symbol : testSymbols) {
            productManager.addProduct(symbol);
        }
        basePrices.put(testSymbols[0], 140.98);
        basePrices.put(testSymbols[1], 174.76);
        basePrices.put(testSymbols[2], 102.11);
        basePrices.put(testSymbols[3], 196.81);

        for(int i=0; i<10000; i++) {
            User randUser = userManager.getRandomUser();
            if(Math.random() < 0.9) {
                String randSymbol = productManager.getRandomProduct();
                BookSide randSide;
                Random random = new Random();
                if(random.nextBoolean() == false)
                    randSide = BookSide.BUY;
                else
                    randSide = BookSide.SELL;
                int randVol = (int) (25 + (Math.random() * 300));
                randVol = (int) Math.round(randVol / 5.0) * 5;
                Price randPrice = getPrice(randSymbol, randSide);
                Order randOrder = new Order(randUser.getUserId(), randSymbol, randPrice, randVol, randSide);
                OrderDTO randOrderDTO = productManager.addOrder(randOrder);
                randUser.addOrder(randOrderDTO);
            } else {
                if(randUser.hasOrderWithRemainingQty() == true) {
                    OrderDTO randOrderDTO = randUser.getOrderWithRemainingQty();
                    OrderDTO cancelledOrderDTO = productManager.cancel(randOrderDTO);
                    if(cancelledOrderDTO != null)
                        randUser.addOrder(cancelledOrderDTO);
                }
            }
        }
        String textBar = "-".repeat(12);
        /*
        System.out.println("\n" + textBar + "\n" +
                            "ProductBooks: \n");
        System.out.println(productManager.toString());

        System.out.println("\n" + textBar + "\n" +
                            "Users: \n");
        System.out.println(userManager.toString());

        */
        System.out.println("\n" + textBar + "\n" +
                            "Market: \n");
        System.out.println("ANN:\n" + ANN.getCurrentMarkets());
        System.out.println("BOB:\n" + BOB.getCurrentMarkets());
        System.out.println("CAT:\n" + CAT.getCurrentMarkets());
        System.out.println("DOG:\n" + DOG.getCurrentMarkets());
        System.out.println("EGG:\n" + EGG.getCurrentMarkets());

        cmp.unSubscribeCurrentMarket("WMT", ANN);
        cmp.unSubscribeCurrentMarket("TGT", ANN);
        cmp.unSubscribeCurrentMarket("TGT", BOB);
        cmp.unSubscribeCurrentMarket("TSLA", BOB);
        cmp.unSubscribeCurrentMarket("AMZN", CAT);
        cmp.unSubscribeCurrentMarket("TGT", CAT);
        cmp.unSubscribeCurrentMarket("WMT", CAT);
        cmp.unSubscribeCurrentMarket("TSLA", DOG);
        cmp.unSubscribeCurrentMarket("WMT", EGG);
    }

    public static Price getPrice(String symbol, BookSide side) {
        Double basePrice = basePrices.get(symbol);
        double priceWidth = 0.02;
        double startPoint = 0.01;
        double tickSize = 0.1;
        double gapFromBase = basePrice * priceWidth; // 5.0
        double priceVariance = gapFromBase * (Math.random());
        double priceToTick = 0;
        if(side == BookSide.BUY) {
            double priceToUse = basePrice * (1 - startPoint);
            priceToUse += priceVariance;
            priceToTick = Math.round(priceToUse * 1/tickSize) / 10.0;
        } else if(side == BookSide.SELL) {
            double priceToUse = basePrice * (1 + startPoint);
            priceToUse -= priceVariance;
            priceToTick = Math.round(priceToUse * 1/tickSize) / 10.0;
        }
        return PriceFactory.makePrice(Double.toString(priceToTick));
    }
}
