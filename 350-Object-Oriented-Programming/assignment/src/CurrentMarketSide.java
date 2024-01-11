public class CurrentMarketSide {
    private final Price price;
    private final int volume;

    public CurrentMarketSide(Price price, int volume) {
        this.price = price;
        this.volume = volume;
    }

    public String toString() {
        if(price == null)
            return "$0.00x0";
        return price.toString() + "x" + volume;
    }
}

