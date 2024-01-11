import java.util.HashMap;

abstract class PriceFactory {
    private static final HashMap<Long, Price> priceMap = new HashMap<>();

    public static Price makePrice(int cents) {
        if (priceMap.containsKey(cents)) {
            return priceMap.get(cents);
        } else {
            Price newPrice = new Price(cents);
            priceMap.put(Integer.toUnsignedLong(cents), newPrice);
            return newPrice;
        }
    }

    public static Price makePrice(String stringValueIn) {
        try {
            stringValueIn = stringValueIn.replace("$", "");
            String[] stringPrice = stringValueIn.split("\\.");
            int cents = Integer.parseInt(stringPrice[0]) * 100 + Integer.parseInt(stringPrice[1]);
            return makePrice(cents); // Use makePrice(int cents) to ensure flyweight behavior
        } catch (Exception e) {
            System.err.println("Invalid string");
        }
        return null;
    }
}


class Price implements Comparable<Price> {
    private int cents;

    public Price(int cents) {

        this.cents = cents;
    }

    public int getPrice() {
        return cents;
    }

    public boolean isNegative() {
        return cents <= 0;
    }

    public Price add(Price p) {
        int sum = cents + p.getPrice();
        return new Price(sum);
    }

    public Price subtract(Price p) {
        int diff = cents - p.getPrice();
        return new Price(diff);
    }

    public Price multiply(int n) {
        int product = cents * n;
        return new Price(product);
    }

    public boolean greaterOrEqual(Price p) {
        return this.cents >= p.getPrice();
    }

    public boolean lessOrEqual(Price p) {
        return this.cents <= p.getPrice();
    }

    public boolean greaterThan(Price p) {
        return this.cents > p.getPrice();
    }

    public boolean lessThan(Price p) {
        return this.cents < p.getPrice();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Price price = (Price) o;
        return cents == price.cents;
    }


    @Override
    public int hashCode() {
        return Integer.hashCode(cents);
    }

    @Override
    public int compareTo(Price p) {
        return this.cents - p.getPrice();
    }

    @Override
    public String toString() {
        int dollars = cents / 100;
        int remainingCents = cents % 100;

        if (remainingCents == 0) {
            return String.format("$%d.00", dollars);
        } else if (remainingCents < 10) {
            return String.format("$%d.0%d", dollars, remainingCents);
        } else {
            return String.format("$%d.%d", dollars, remainingCents);
        }
    }

}

