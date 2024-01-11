import java.util.HashMap;
import java.util.Random;

public class ProductManager {
    private static ProductManager instance = new ProductManager();
    public HashMap<String, ProductBook> productBooks;

    private ProductManager() {
        productBooks = new HashMap<>();
    }

    public static ProductManager getInstance() {
        return instance;
    }

    public void addProduct(String symbol) throws DataValidationException {
        if (!productBooks.containsKey(symbol)) {
            ProductBook productBook = new ProductBook(symbol);
            productBooks.put(symbol, productBook);
        }
    }

    public String getRandomProduct() {
        Random random = new Random();
        int stopIndex = random.nextInt(productBooks.size());
        for (String symbol : productBooks.keySet()) {
            if (stopIndex == 0) {
                return symbol;
            }
            stopIndex--;
        }
        return null; // NO PRODUCTS EXCEPTION HERE
    }


    public OrderDTO addOrder(Order o) throws DataValidationException {
        String symbol = o.getProduct();
        ProductBook book = productBooks.get(symbol);
        book.add(o);
        return o.makeTradableDTO();
    }

    public OrderDTO cancel(OrderDTO o) throws OrderNotFoundException {
        String symbol = o.product;
        ProductBook book = productBooks.get(symbol);
        if (book != null) {
            return book.cancel(o.side, o.id);
        }
        System.out.println("Failed to cancel " + symbol);
        return null;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (ProductBook productBook : productBooks.values()) {
            result.append(productBook.toString()).append("\n");
        }
        return result.toString();
    }
}
