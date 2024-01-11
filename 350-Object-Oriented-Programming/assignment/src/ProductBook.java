import java.util.Random;

public class ProductBook {
    

    private final String product;
    private final ProductBookSide buySide;
    private final ProductBookSide sellSide;

    public ProductBook(String product) throws DataValidationException {
        if (product == null || !product.matches("^[a-zA-Z0-9.]{1,5}$")) {
            throw new DataValidationException("Invalid product");
        }

        this.product = product;
        buySide = new ProductBookSide(ProductBookSide.BookSide.BUY);
        sellSide = new ProductBookSide(ProductBookSide.BookSide.SELL);
    }

    public OrderDTO add(Order o) throws DataValidationException {
        OrderDTO orderDTO;
        BookSide side = o.getSide();
        if (side == BookSide.BUY) {
            orderDTO = buySide.add(o);
            System.out.print("ADD: BUY: ");
        } else if (side == BookSide.SELL) {
            orderDTO = sellSide.add(o);
            System.out.print("ADD: SELL: ");
        } else {
            throw new DataValidationException("Invalid order side");
        }
        System.out.println(o.toString());
        tryTrade();
        updateMarket();
        return orderDTO;
    }

    public OrderDTO cancel(BookSide side, String orderId) throws OrderNotFoundException {
        OrderDTO orderDTO;
        if (side == BookSide.BUY) {
            orderDTO = buySide.cancel(orderId);
        } else if (side == BookSide.SELL) {
            orderDTO = sellSide.cancel(orderId);
        } else {
            throw new OrderNotFoundException("Order not found");
        }
        updateMarket();
        return orderDTO;
    }

    public void tryTrade() {
        Price topBuy = buySide.topOfBookPrice();
        Price topSell = sellSide.topOfBookPrice();
        while (topBuy != null && topSell != null && topBuy.greaterOrEqual(topSell)) {
            int buyVolume = buySide.topOfBookVolume();
            int sellVolume = sellSide.topOfBookVolume();
            int tradeVol = Math.min(buyVolume, sellVolume);
            sellSide.tradeOut(topSell, tradeVol);
            buySide.tradeOut(topBuy, tradeVol);
            topBuy = buySide.topOfBookPrice();
            topSell = sellSide.topOfBookPrice();
        }
    }

    public BookSide getRandomSide() {
        Random random = new Random();
        boolean randBool = random.nextBoolean();
        if(randBool == false)
            return BookSide.BUY;
        else
            return BookSide.SELL;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("Product: ").append(product).append("\n");
        builder.append(buySide.toString());
        builder.append(sellSide.toString());

        return builder.toString();
    }

    private void updateMarket() {
        Price buyPrice = buySide.topOfBookPrice();
        int buyVolume = buySide.topOfBookVolume();
        Price sellPrice = sellSide.topOfBookPrice();
        int sellVolume = sellSide.topOfBookVolume();

        CurrentMarketTracker.getInstance().updateMarket(product, buyPrice, buyVolume, sellPrice, sellVolume);
    }
}
