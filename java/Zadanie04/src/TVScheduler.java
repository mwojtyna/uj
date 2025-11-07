import java.util.*;

class TVScheduler implements Scheduler {
    private final List<Slot> programs = new ArrayList<>();

    public static void main(String[] args) {
        {
            TVScheduler scheduler = new TVScheduler();
            scheduler.addSlot(new Slot("TV1", "green", 10, 0, 60));
            scheduler.addSlot(new Slot("TV1", "red", 11, 1, 60));
            scheduler.addSlot(new Slot("TV1", "pink", 12, 2, 90));
            scheduler.addSlot(new Slot("TV1", "gray", 13, 40, 60));
            scheduler.addSlot(new Slot("TV1", "green", 14, 41, 30));
            scheduler.addSlot(new Slot("TV1", "gray", 15, 12, 60));

            scheduler.addSlot(new Slot("TV2", "yellow", 10, 0, 120));
            scheduler.addSlot(new Slot("TV2", "blue", 12, 1, 90));
            scheduler.addSlot(new Slot("TV2", "yellow", 13, 32, 150));

            scheduler.addSlot(new Slot("TV3", "beige", 10, 0, 150));
            scheduler.addSlot(new Slot("TV3", "brown", 12, 31, 60));
            scheduler.addSlot(new Slot("TV3", "darkblue", 13, 32, 60));
            scheduler.addSlot(new Slot("TV3", "brown", 14, 33, 30));
            scheduler.addSlot(new Slot("TV3", "white", 15, 4, 30));
            scheduler.addSlot(new Slot("TV3", "darkblue", 15, 35, 30));

            System.out.println(scheduler.match(Set.of("yellow", "gray", "darkblue")));
        }
        {
            TVScheduler scheduler = new TVScheduler();

            scheduler.addSlot(new Slot("TV1", "Zielony", 10, 0, 90));
            scheduler.addSlot(new Slot("TV1", "Czerwony", 11, 31, 60));
            scheduler.addSlot(new Slot("TV1", "Różowy", 12, 32, 75));
            scheduler.addSlot(new Slot("TV1", "Szary", 13, 48, 30));
            scheduler.addSlot(new Slot("TV1", "Zielony", 14, 19, 30));
            scheduler.addSlot(new Slot("TV1", "Szary", 14, 50, 45));

            // --- TV2 ---
            scheduler.addSlot(new Slot("TV2", "Żółty", 10, 0, 135));
            scheduler.addSlot(new Slot("TV2", "Niebieski", 12, 16, 90));
            scheduler.addSlot(new Slot("TV2", "Żółty", 13, 47, 135));

            // --- TV3 ---
            scheduler.addSlot(new Slot("TV3", "Złoty", 10, 0, 165));
            scheduler.addSlot(new Slot("TV3", "Brązowy", 12, 46, 60));
            scheduler.addSlot(new Slot("TV3", "Granatowy", 13, 47, 30));
            scheduler.addSlot(new Slot("TV3", "Brązowy", 14, 18, 45));
            scheduler.addSlot(new Slot("TV3", "Biały", 15, 4, 30));
            scheduler.addSlot(new Slot("TV3", "Granatowy", 15, 35, 30));
            scheduler.addSlot(new Slot("PERF", "P1", 10, 0, 10));
            scheduler.addSlot(new Slot("PERF", "P2", 10, 11, 10));
            scheduler.addSlot(new Slot("PERF", "P3", 10, 22, 10));
            scheduler.addSlot(new Slot("PERF", "P4", 10, 33, 10));
            scheduler.addSlot(new Slot("PERF", "P5", 10, 44, 10));
            scheduler.addSlot(new Slot("PERF", "P6", 10, 55, 10));
            scheduler.addSlot(new Slot("PERF", "P7", 11, 6, 10));
            scheduler.addSlot(new Slot("PERF", "P8", 11, 17, 10));

            System.out.println(scheduler.match(Set.of("P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8")));
        }
    }

    @Override
    public void addSlot(Slot program) {
        this.programs.add(program);
    }

    @Override
    public Set<List<Slot>> match(Set<String> favoriteNames) {
        List<Slot> favorites = this.programs.stream().filter(x -> favoriteNames.contains(x.program())).toList();
        Set<Slot> cur = new HashSet<>();
        Set<String> curNames = new HashSet<>();
        Set<List<Slot>> res = new HashSet<>();

        backtrack(favorites, favoriteNames.size(), cur, curNames, res, 0);

        return res;
    }

    private void backtrack(List<Slot> favorites, int favoriteNamesCount, Set<Slot> cur, Set<String> curNames, Set<List<Slot>> res, int start) {
        if (start == favorites.size()) {
            if (cur.size() == favoriteNamesCount) {
                res.add(new ArrayList<>(cur));
            }
            return;
        }

        for (int i = start; i < favorites.size(); i++) {
            Slot program = favorites.get(i);
            if (!curNames.contains(program.program()) && mutuallyExclusive(cur, program)) {
                cur.add(program);
                curNames.add(program.program());
                backtrack(favorites, favoriteNamesCount, cur, curNames, res, i + 1);
                curNames.remove(program.program());
                cur.remove(program);
            }

            backtrack(favorites, favoriteNamesCount, cur, curNames, res, i + 1);
        }
    }

    private boolean mutuallyExclusive(Set<Slot> programs, Slot program) {
        int programTimeStart = calculateSlotStart(program);
        int programTimeEnd = programTimeStart + program.duration();

        for (Slot cur : programs) {
            int curTimeStart = calculateSlotStart(cur);
            int curTimeEnd = curTimeStart + cur.duration();

            if (curTimeEnd >= programTimeStart && programTimeEnd >= curTimeStart) {
                return false;
            }
        }

        return true;
    }

    private int calculateSlotStart(Slot slot) {
        return slot.atH() * 60 + slot.atM();
    }
}
