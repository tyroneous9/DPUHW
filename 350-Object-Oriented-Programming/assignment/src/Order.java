import java.util.Objects;

public class Order {
    private final String user;
    private final String product;
    private final Price price;
    private final BookSide side;
    private final String id;
    private final int originalVolume;
    private int remainingVolume;
    private int cancelledVolume;
    private int filledVolume;

    public Order(String user, String product, Price price, int originalVolume, BookSide side) throws DataValidationException {
        if (user.matches("^[A-Z]{3}$")
            && product.matches("^[A-Za-z0-9.]{1,5}$") 
            && price != null
            && side != null
            && originalVolume > 0 
            && originalVolume < 10000) 
        {
            this.user = user;
            this.product = product;
            this.price = price;
            this.side = side;
            this.originalVolume = originalVolume;
            this.remainingVolume = originalVolume;
            this.cancelledVolume = 0;
            this.filledVolume = 0;
            this.id = user + product + price.toString() + System.nanoTime();
        } else {
            throw new DataValidationException("Invalid order");
        }
    }

    public String getUser() {
        return user;
    }

    public String getProduct() {
        return product;
    }

    public Price getPrice() {
        return price;
    }

    public BookSide getSide() {
        return side;
    }

    public String getId() {
        return id;
    }

    public int getOriginalVolume() {
        return originalVolume;
    }

    public int getRemainingVolume() {
        return remainingVolume;
    }

    public int getCancelledVolume() {
        return cancelledVolume;
    }

    public int getFilledVolume() {
        return filledVolume;
    }

    public void setRemainingVolume(int remainingVolume) {
        this.remainingVolume = remainingVolume;
    }

    public void setCancelledVolume(int cancelledVolume) {
        this.cancelledVolume = cancelledVolume;
    }

    public void setFilledVolume(int filledVolume) {
        this.filledVolume = filledVolume;
    }

    @Override
    public String toString() {
        String str = user + " order: " + side + " " + product + " at " + price.toString() +
            ", Orig Vol: " + originalVolume + ", Rem Vol: " + remainingVolume +
            ", Fill Vol: " + filledVolume + ", CXL Vol: " + cancelledVolume +
            ", ID: " + id;
        return str;
    }

    public OrderDTO makeTradableDTO() {
        return new OrderDTO(user, product, price, side, originalVolume, remainingVolume, cancelledVolume, filledVolume, id);
    }
}
