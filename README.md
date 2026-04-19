# ACMSE 2026 Undergraduate Programming Contest Submission

Team: Brand Recognition

## Project structure

```
├───src
├───test
│   ├───images
│   └───masks  <-- Output location
└───train
    ├───images
    └───masks
```

## Usage
To build: (project has a precompiled windows binary at `/src/main`)
```
./src/build.sh
```

To run:
```
./src/main <filename> <delta>
```
Output will be located at `/src/output.png`

## Operation
![Step 1](diagrams/step1.png)
![Step 2bc](diagrams/step2b2c.png)
![Step 2c3](diagrams/step2c3.png)
![Step 4a4b](diagrams/step4a4b.png)

## Examples
Example 1(delta = 15):
![Example 1](diagrams/EX1.png)

Example 2(delta = 100):
![Example 2](diagrams/EX2.png)

Mask from the provided masks (colorized):

![Example Mask](diagrams/15088Mask.png)