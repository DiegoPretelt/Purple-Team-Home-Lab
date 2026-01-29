# Console Login Failure

## Summary
Detects a modifiable amount of logon failures by an IAM user in a modifiable amount of time.

## Data Source
- AWS CloudTrail (CloudWatch Logs: /cloudsoc/cloudtrail)

## Detection Logic
**Metric Filter Pattern**
```text
{ ($.eventName = "ConsoleLogin") && ($.errorMessage = "Failed authentication") }
