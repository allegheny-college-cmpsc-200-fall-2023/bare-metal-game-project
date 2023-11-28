# CMPSC 200: Stellar Cartography

|Deadline | Time |
|:--------|:-----|
|December 15 | 12:00p (noon) |

So far, our missions have concentrated on the _known_ universe and the many rocks it contains. However, there are many, many more rocks out there. Like..._many_. Our job? To boldy go where no rock miner has gone before. Competitively.

We're looking for the most adventurous, foolish, brave, and rock-dollar-hungry miners to take data we've been gathering and _map it_. There's a lot of data, so there are a lot of maps. There are also many tricks that you might use to make your mapping process _faster than anyone else's_.

tl;dr: you're mapping sectors of space based on data provided in order to map the _most_ maps in the period between now and the end of our time together.

## Rules

* All maps must be retrieved from the central map data server at `metal.cmpsc200.chompe.rs`
* Maps must be processed by Pico devices using programs written in `C`
* Maps must be uploaded _back_ to `metal.cmpsc200.chompe.rs` using processing code
  * Only maps which are _both uploaded_ and _correct_ will receive the vaunted `rock dollars`

### Maps

Maps are composed of features (`#`) and natural ground (`.`) arranged in `blocks` or `tiles` (they're the same thing). A _finished_ map might look like the following:
```
############################################
######################################..####
######################################...###
############################################
############################################
############################################
############################################
############################################
############################################
############################################
##############..######..##########...#######
#######...#####..####......#######...#######
#######....##########......########...######
########...###########.....#########...#####
#######################...###########..#####
########################.###################
############################################
############################################
############################################
############################################
############################################
############################################
############################################
```
Maps have three basic features:

* a `sector_height` measure (rows in map readout)
* a `sector_width` measure (columns in map readout)
* a `sector_toplogy` score 
  * geological likelihood (percentage) of topological features (i.e. rocks or mountains)

The first two, `sector_height`, `sector_width` are somewhat clear. However, the last has some additional pieces and assumptions based on our mapping process which involves two steps:

* making a `base map`
* applying `toplogy` rules

### Making a base map

Base maps are maps made from the general data. For example, a map described by:
```
sector_height:      20
sector_width:       30
sector_topology:    50
```
Would could a base map that looks something like:
```
##############################
##..#...##...##..##..##.....##
#.##..##........##..#.#.#..#.#
#.#...#.#..#..######..###..#.#
#.##.###.###.#.##.#...#.#.##.#
#.##..#..##.#.##.##.##.###.#.#
##.####.###.#.###.#######....#
#..#.###.#.#..#.#.#####..#.###
###..#..#...#.#...####.....###
#.#.##....#...##..#....#.#.#.#
#............................#
#..#.##.####.##.#.#.##.#...#.#
####..#..###..#.#.#.#..##.#.##
###..#.#######..#.#####.###.##
#.#.#..#..##...#.#.#...####..#
#####..###.####..#..##########
####..##..#....#.#.....##....#
#.#.##..#..#.##.##.##...##..##
#.....#.#...#####.###.#.###.##
##############################
```
There are a couple guidelines about base maps that we need to follow:

* all outer edges are topological features (marked by `#`)
* the very middle of the map _never_ has a topological feature (marked `.`)
* every other space has a _chance_ of having a topological feature (chance equal to our `sector_topology` score)

### Applying a topology

It seems like the terrain should be more well defined. For example, a fully resolved map might look like:
```
##############################
##########...#################
####.####.....################
#########.....######.#########
###########...################
############..################
############..################
############...########...####
############.....#####....####
######......................##
######......................##
######....#.................##
#######..###................##
#############...........##..##
##############.........#######
##############.........#######
###############........#######
#################..#...#######
##############################
##############################
```
Here, we employ some of our science<sup>TM</sup>. Namely the following notes about _adjacency_:

1. if a spot on the grid has a toplogical feature (`#`) and _is surrounded by at least `4` more in a `1`-block radius, we're pretty sure it's definitely a `#`
2. if a spot on the grid has a toplogical feature (`#`) and _is surrounded by fewer than `2` toplogical feature markers (`#`), we're pretty sure it should be natural ground (`.`)
3. in the event that any spot (_feature or not_) has `5` or more features marked (`#`) within a `1`-block radius, that spot should be a feature (`#`)

#### Examples

> Note that maps do not contain `[` or `]` characters; these are included to demonstrate which tile we're interested in testing our "rule" on.

##### Rule 1

The following should _stay_ a `#`.

```
...........
....#......
...#[#]#...
.....#.....
...........
```

##### Rule 2

The following should change to a `.`.

```
...........
...........
....[#]#...
.....#.....
...........
```

##### Rule 3

The following should become a `#`.

```
...........
....##.....
...#[.]#...
.....#.....
...........
```

## Suggestions

You should consider the following something of canonical advice for figuring up a way to achieve this mapping task.

* use a `struct` pointer to allocate map measurements and, possibly, a `2D` array to store the generated map
* for the generated map, it might work best to use _numbers_ to represent the states of topology; a reasonable system:

|Number |Mark |Meaning |
|:------|:----|:-------|
|0      |`.`  |Natural ground |
|1      |`#`  |Topological feature |

* the reason for the above: there _may_ come a time when additional symbols are added based on our advanced understanding of mapping these areas
  * it's also easier to pick indexes from an `array` than store absolute characters
* when moving from a `base map` to an applied `topology`, recall that you're making a `2D` array -- this is helpful when calculating _adjacency_

## Note on competition

The competition here _does not_ impact your assessment directly (though, folks who reach the top of the league table are probably doing something _right_). Everyone starts out on equal footing with the same knowledge. How can you take your knowledge of hacks, tricks, and clever misuses and put it to work?

## Changes to files in `.vscode`

As with all of our assignments, you will need switch out the `.vscode` folder in each exercise with the _last working copy_.

See our [wiki's entry  on "Configuring Assignments"](https://github.com/allegheny-college-cmpsc-200-fall-2023/course-materials/wiki/03-Configuring-Assignments)
for more information.
