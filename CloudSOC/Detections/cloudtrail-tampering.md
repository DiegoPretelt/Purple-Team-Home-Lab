# CloudTrail Tampering

## Summary
This detects any attempt at defense evasion by erasing Trails from cloudtrail or stopping logging entirely.

## Data Source
- AWS CloudTrail (CloudWatch Logs: /cloudsoc/cloudtrail)

## Detection Logic
**Metric Filter Pattern**
```text
{ ($.eventName = "StopLogging") || ($.eventName = "DeleteTrail") }
