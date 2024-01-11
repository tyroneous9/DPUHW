public class OrderDTO {
    public final String user;
    public final String product;
    public final Price price;
    public final BookSide side;
    public final String id;
    public final int originalVolume;
    public final int remainingVolume;
    public final int cancelledVolume;
    public final int filledVolume;

    public OrderDTO(String user, String product, Price price, BookSide side, int originalVolume, int remainingVolume, int cancelledVolume, int filledVolume, String id) {
        this.user = user;
        this.product = product;
        this.price = price;
        this.side = side;
        this.originalVolume = originalVolume;
        this.remainingVolume = remainingVolume;
        this.cancelledVolume = cancelledVolume;
        this.filledVolume = filledVolume;
        this.id = id;
    }

    @Override
    public String toString() {
        String str = user + " order: " + side + " " + product + " at " + price.toString() +
            ", Orig Vol: " + originalVolume + ", Rem Vol: " + remainingVolume +
            ", Fill Vol: " + filledVolume + ", CXL Vol: " + cancelledVolume +
            ", ID: " + id;
        return str;
    }
}
