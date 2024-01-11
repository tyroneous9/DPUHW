package automata;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class Test {
  static class StopWatch {
    private long duration = 0;
    private long starttime = 0;

    public StopWatch () {
    }

    public void start () {
      starttime = System.currentTimeMillis ();
    }

    public void stop () {
      duration += System.currentTimeMillis () - starttime;
    }

    public long duration () {
      return duration;
    }
  }

  static class TestException extends Exception {
    static final long serialVersionUID = 314;

    final double value;

    public TestException (String msg, double val) {
      super (msg);
      this.value = val;
    }

    public TestException (String msg) {
      super (msg);
      this.value = 0;
    }
  }

  static public int timeout = 10;

  static public Double runTest (String name, Callable<Void> test, int points) {
    ExecutorService executor = Executors.newCachedThreadPool ();
    Future<Void> future = executor.submit (test);
    String overPts = points + "pt" + (points == 1 ? "" : "s");
    try {
      future.get (timeout, TimeUnit.SECONDS);
      System.err.println ("[OK] " + name + " (" + overPts + ")");
      return (double) points;
    } catch (TimeoutException e) {
      System.err.println ("[KO] " + name + " (0/" + overPts + "): Timeout");
      return 0.;
    } catch (ExecutionException | InterruptedException e) {
      if (e.getCause () instanceof TestException) {
        TestException te = (TestException) e.getCause ();
        if (te.value > 0)
          System.err.println ("[~~] " + name + " (" + te.value * points + "/" + overPts + "): " +
              te.getMessage ());
        else
          System.err.println ("[KO] " + name + " (0/" + overPts + "): " +
              te.getMessage ());
        return te.value * points;
      } else {
        System.err.print ("[KO] " + name + " (0/" + overPts + "): ");
        e.getCause ().printStackTrace ();
        return 0.;
      }
    }
  }
}
